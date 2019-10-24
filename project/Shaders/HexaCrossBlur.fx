//=====================================
//
//ヘキサクロスブラーシェーダ[HexaCrossBlur.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/*********************************
グローバル変数
*********************************/
float texelU[5];	//近傍テクセル位置1
float texelV[5];	//近傍テクセル位置1

/*********************************
テクスチャサンプラ
*********************************/
sampler s0 : register(s0);

/*********************************
頂点シェーダ出力構造体
*********************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

/*********************************
頂点シェーダ
*********************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float2 tex : TEXCOORD0
) {
	VS_OUTPUT Out;

	Out.pos = pos;
	Out.tex = tex;

	return Out;
}

/*********************************
ピクセルカラー取得処理
*********************************/
float4 GetPixelColor(float2 texel[6])
{
	float4 p0 = tex2D(s0, texel[0]) * 0.40f;
	float4 p1 = tex2D(s0, texel[1]) * 0.18f;
	float4 p2 = tex2D(s0, texel[2]) * 0.15f;
	float4 p3 = tex2D(s0, texel[3]) * 0.12f;
	float4 p4 = tex2D(s0, texel[4]) * 0.09f;
	float4 p5 = tex2D(s0, texel[5]) * 0.06f;

	return p0 + p1 + p2 + p3 + p4 + p5;
}

/*********************************
ピクセルシェーダ(上)
*********************************/
float4 PS1(VS_OUTPUT In) : COLOR0
{
	float2 texel[6];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(0.0f, -texelV[0]);
	texel[2] = In.tex + float2(0.0f, -texelV[1]);
	texel[3] = In.tex + float2(0.0f, -texelV[2]);
	texel[4] = In.tex + float2(0.0f, -texelV[3]);
	texel[5] = In.tex + float2(0.0f, -texelV[4]);

	return GetPixelColor(texel);
}

/*********************************
ピクセルシェーダ(右上)
*********************************/
float4 PS2(VS_OUTPUT In) : COLOR0
{
	float2 texel[6];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(texelU[1], -texelV[1]);
	texel[3] = In.tex + float2(texelU[2], -texelV[2]);
	texel[4] = In.tex + float2(texelU[3], -texelV[3]);
	texel[5] = In.tex + float2(texelU[4], -texelV[4]);

	return GetPixelColor(texel);
}

/*********************************
ピクセルシェーダ(右下)
******************************* **/
float4 PS3(VS_OUTPUT In) : COLOR0
{
	float2 texel[6];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(texelU[0], texelV[0]);
	texel[2] = In.tex + float2(texelU[1], texelV[1]);
	texel[3] = In.tex + float2(texelU[2], texelV[2]);
	texel[4] = In.tex + float2(texelU[3], texelV[3]);
	texel[5] = In.tex + float2(texelU[4], texelV[4]);

	return GetPixelColor(texel);
}
/*********************************
ピクセルシェーダ(下)
*********************************/
float4 PS4(VS_OUTPUT In) : COLOR0
{
	float2 texel[6];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(0.0f, texelV[0]);
	texel[2] = In.tex + float2(0.0f, texelV[1]);
	texel[3] = In.tex + float2(0.0f, texelV[2]);
	texel[4] = In.tex + float2(0.0f, texelV[3]);
	texel[5] = In.tex + float2(0.0f, texelV[4]);

	return GetPixelColor(texel);
}
/*********************************
ピクセルシェーダ(左下)
*********************************/
float4 PS5(VS_OUTPUT In) : COLOR0
{
	float2 texel[6];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(-texelU[0], texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], texelV[1]);
	texel[3] = In.tex + float2(-texelU[2], texelV[2]);
	texel[4] = In.tex + float2(-texelU[3], texelV[3]);
	texel[5] = In.tex + float2(-texelU[4], texelV[4]);

	return GetPixelColor(texel);
}

/*********************************
ピクセルシェーダ(左上)
*********************************/
float4 PS6(VS_OUTPUT In) : COLOR0
{
	float2 texel[6];

	texel[0] = In.tex;
	texel[1] = In.tex + float2(-texelU[0], -texelV[0]);
	texel[2] = In.tex + float2(-texelU[1], -texelV[1]);
	texel[3] = In.tex + float2(-texelU[2], -texelV[2]);
	texel[4] = In.tex + float2(-texelU[3], -texelV[3]);
	texel[5] = In.tex + float2(-texelU[4], -texelV[4]);

	return GetPixelColor(texel);
}

/*********************************
テクニック
*********************************/
technique tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS1();
	}

	pass P1
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS2();
	}

	pass P2
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS3();
	}

	pass P3
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS4();
	}

	pass P4
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS5();
	}

	pass P5
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS6();
	}

};