//=====================================
//
//クロスブラーシェーダ[CrossBlur.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/***************************************
グローバル変数
***************************************/
float texelU[2];			//X方向の隣のテクセルの位置
float texelV[2];			//Y方向の隣のテクセルの位置

sampler s0 : register(s0);	//テクスチャサンプラ

/*********************************************
頂点シェーダ出力構造体
*********************************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

/*********************************************
頂点シェーダ
*********************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float2 tex : TEXCOORD0
) {
	VS_OUTPUT Out;

	Out.pos = pos;
	Out.tex = tex;

	return Out;
}

/*********************************************
ピクセルカラー取得処理
*********************************************/
float4 GetPixelColor(float2 texel[3])
{
	float4 p0 = tex2D(s0, texel[0]) * 0.5f;
	float4 p1 = tex2D(s0, texel[1]) * 0.3f;
	float4 p2 = tex2D(s0, texel[2]) * 0.2f;

	return p0 + p1 + p2;
}

/********************************************
ピクセルシェーダ（右上）
*********************************************/
float4 PS1(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(texelU[1], -texelV[1]);

	return GetPixelColor(texel);
}

/********************************************
ピクセルシェーダ（右下）
*********************************************/
float4 PS2(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], texelV[0]);
	texel[2] = In.tex + float2(texelU[1], texelV[1]);
	
	return GetPixelColor(texel);
}

/********************************************
ピクセルシェーダ（左上）
*********************************************/
float4 PS3(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(-texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], -texelV[1]);

	return GetPixelColor(texel);
}

/********************************************
ピクセルシェーダ（左下）
*********************************************/
float4 PS4(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(-texelU[0], texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], texelV[1]);

	return GetPixelColor(texel);
}

/********************************************
ピクセルシェーダ出力構造体（1パス用）
*********************************************/
struct PS_OUTPUT {
	float4 color0 : COLOR0;
	float4 color1 : COLOR1;
	float4 color2 : COLOR2;
	float4 color3 : COLOR3;
};

/********************************************
ピクセルシェーダ（１パスで4方向にブラー）
*********************************************/
float4 PS5(VS_OUTPUT In) : COLOR0
{
	float2 texel[3];
	float4 color;
	const float magni = 0.6f;	//減衰率（4方向の結果をそのまま合成すると飽和するので）

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(texelU[1], -texelV[1]);

	color = GetPixelColor(texel) * magni;

	texel[1] = In.tex + float2(texelU[0], texelV[0]);
	texel[2] = In.tex + float2(texelU[1], texelV[1]);

	color += GetPixelColor(texel) * magni;

	texel[1] = In.tex + float2(-texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], -texelV[1]);

	color += GetPixelColor(texel) * magni;

	texel[1] = In.tex + float2(-texelU[0], texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], texelV[1]);

	color += GetPixelColor(texel) * magni;

	return color;
}

/********************************************
テクニック
*********************************************/
technique tech
{
	pass P0
	{
		ZWRITEENABLE = false;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS1();
	}

	pass P1
	{
		ZWRITEENABLE = false;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS2();
	}

	pass P2
	{
		ZWRITEENABLE = false;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS3();
	}

	pass P3
	{
		ZWRITEENABLE = false;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS4();
	}

	pass P4
	{
		ZWRITEENABLE = false;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS5();
	}
};