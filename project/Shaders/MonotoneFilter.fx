//=====================================
//
//モノトーンシェーダ[MonotoneFilter.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/***************************************
グローバル変数
***************************************/
float power;		//モノトーンの強さ

/***************************************
テクスチャサンプラ
***************************************/
sampler tex0 : register(s0);	//テクスチャサンプラー

/***************************************
頂点シェーダ出力構造体
***************************************/
struct VS_OUTPUT {
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

/***************************************
頂点シェーダ
***************************************/
VS_OUTPUT VS(
	float4 Pos : POSITION,
	float4 Col : COLOR0,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.Pos = Pos;
	Out.Tex = Tex;

	return Out;
}

/***************************************
ピクセルシェーダ
***************************************/
float4 PS(VS_OUTPUT In) : COLOR
{
	float4 Out = tex2D(tex0, In.Tex);
	float4 Col = tex2D(tex0, In.Tex);

	//モノトーン化した色
	Col.rgb = (Col.r + Col.g + Col.b) * 0.333f;

	//線形合成
	Out.r = Out.r * (1.0f - power) + Col.r * power;
	Out.g = Out.g * (1.0f - power) + Col.g * power;
	Out.b = Out.b * (1.0f - power) + Col.b * power;

	return Out;
}

/***************************************
テクニック
***************************************/
technique tech {
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
}