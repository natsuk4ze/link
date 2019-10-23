//=====================================
//
// DepthRenderer.fx
// 機能:深度バッファシャドウシェーダ
// Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
グローバル変数
***************************************/
float4x4 mtxWVP;
float4x4 mtxLWVP;
float4x4 mtxLWVPT;
float4 lightDir;

sampler tex1 : register(s1);

/**************************************
頂点シェーダ出力構造体
***************************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 color : COLOR0;
	float2 tex : TEXCOORD0;
	float2 depth : TEXCOORD1;
	float4 lightUV : TEXCOORD2;
};

/**************************************
頂点シェーダ
***************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float4 normal : NORMAL,
	float2 tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.pos = mul(pos, mtxWVP);

	Out.tex = tex;

	//光源計算
	float3 L = -lightDir.xyz;
	float3 N = normalize(normal.xyz);
	Out.color = max(0.0f, dot(N, L)) * float4(0.0f, 0.6f, 1.0f, 1.0f);
	Out.color.a = 1.0f;

	//正射影座標系に変換したZ値を計算
	Out.depth.xy = mul(pos, mtxLWVP).zw;

	//テクスチャ座標系に変換した頂点座標を計算
	Out.lightUV = mul(pos, mtxLWVPT);

	return Out;
}

/**************************************
ピクセルシェーダ
***************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out = In.color;

	//Zバッファから深度値を取得
	float d = tex2Dproj(tex1, In.lightUV).r;

	if (In.depth.x > d + 0.005f)
	{
		Out.rgb *= 0.1f;
		//Out.rgb = float3(1.0f, 1.0f, 1.0f) - Out.rgb;
	}

	return Out;
}

/**************************************
テクニック
***************************************/
technique tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};