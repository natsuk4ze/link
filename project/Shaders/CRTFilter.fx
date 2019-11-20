//=====================================
//
// CRTフィルター[CRTFilter.h]
// Author:GP12B332 19 染谷武志
//
//=====================================

/***************************************
グローバル変数
***************************************/
float Time;
float2 ScreenParams;
float SinNoiseWidth = 1.0f;
float SinNoiseScale = 1.0f;
float SinNoiseOffset = 1.0f;
float ScanLineTail = 0.5f;
float ScanLineSpeed = 5.0f;

/***************************************
ランダムでフラクタル値を取得する関数
***************************************/
float rand(float2 co) {
	return frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453);
}

/***************************************
範囲内の値をランダムで取得する関数
***************************************/
float Range(float min, float max) {
	return (float)rand(float2(min, max)) / 65565 * (max - min) + min;
}

/***************************************
テクスチャサンプラ
***************************************/
sampler s0 : register(s0);	//テクスチャサンプラー
sampler s1 : register(s1);

/***************************************
頂点シェーダ出力構造体
***************************************/
struct VS_OUTPUT {
	float4 vertex : POSITION;
	float2 UV : TEXCOORD0;
};

/***************************************
頂点シェーダ
***************************************/
VS_OUTPUT VS(float4 vertex : POSITION,
	float2 UV : TEXCOORD0)
{
	VS_OUTPUT Out;
	Out.vertex = vertex;
	Out.UV = UV;

	return Out;
}

/***************************************
ピクセルシェーダ0
***************************************/
float4 PS0(VS_OUTPUT In) : COLOR
{
	float2 uv = In.UV + 0.5f;

	// UV座標を再計算し、画面を歪ませる
	float vignet = length(uv);
	uv /= 1 - vignet * 0.2f;
	float2 texUV = In.UV + 0.5f;

	// 色を計算
	float3 col;

	// ノイズ、オフセットを適用
	float NoiseX = Range(0, 1);
	texUV.x += sin(texUV.y * SinNoiseWidth + SinNoiseOffset) * SinNoiseScale;
	//texUV += Offset;
	texUV.x += tex2D(s1, In.UV).r * NoiseX;
	texUV = fmod(texUV, 1);

	// 色を取得、RGBを少しずつずらす
	col.r = tex2D(s0, In.UV).r;
	col.g = tex2D(s0, In.UV - float2(0.002f, 0.0f)).g;
	col.b = tex2D(s0, In.UV - float2(0.004f, 0.0f)).b;

	return float4(col, 1.0f);
}


/***************************************
ピクセルシェーダ1
***************************************/
float4 PS1(VS_OUTPUT In) : COLOR
{
	// 色を取得
	float4 col = tex2D(s0, In.UV);

	// RGBノイズ
	float RGBNoise = Range(0, 1);
	if (tex2D(s1, In.UV + float2(Time, Time)).r * 0.01f < RGBNoise)
	{
		float tmp = 123 + Time;
		col.r = tex2D(s1, In.UV + float2(tmp, 0)).r;
		col.g = tex2D(s1, In.UV + float2(tmp, 1)).g;
		col.b = tex2D(s1, In.UV + float2(tmp, 2)).b;
	}

	// 出力
	return col;
}

/***************************************
ピクセルシェーダ2
***************************************/
float4 PS2(VS_OUTPUT In) : COLOR
{
	float4 col = tex2D(s0, In.UV);

	// ピクセルごとに描画するRGBを決める
	float floorX = fmod(In.UV.x * ScreenParams.x / 3.0f, 1.0f);
	col.r *= floorX > 0.3333;
	col.g *= floorX < 0.3333 || floorX > 0.6666;
	col.b *= floorX < 0.6666;

	// 出力
	return col;
}

/***************************************
ピクセルシェーダ3
***************************************/
float4 PS3(VS_OUTPUT In) : COLOR
{
	float4 col = tex2D(s0, In.UV);

	// スキャンラインを描画
	float scanLineColor = sin(Time * 10.0f + In.UV.y * 500.0f) / 2.0f + 0.5f;
	col *= 0.5f + clamp((frac(In.UV.y + Time * ScanLineSpeed) - 1.0f + ScanLineTail) / min(ScanLineTail, 1.0f), 0, 1);
	
	// スキャンラインの残像を描画
	float tail = clamp(frac(In.UV.y + Time * ScanLineSpeed) - 1.0f + ScanLineTail / min(ScanLineTail, 1.0f), 0, 1);
	col *= tail * 0.2f;

	// 出力
	return col;
}

/***************************************
テクニック
***************************************/
technique tech {
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS0();
	}
	pass P1
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS1();
	}
	pass P2
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS2();
	}
	pass P3
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS3();
	}
}