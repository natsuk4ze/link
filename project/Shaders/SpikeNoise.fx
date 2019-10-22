//=====================================
//
//スパイクノイズシェーダ[SpikeNoise.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/***************************************
グローバル変数
***************************************/
float length;		//ノイズの強さ
float baseY;	

/***************************************
テクスチャサンプラ
***************************************/
sampler s0 : register(s0);

/***************************************
頂点シェーダ出力構造体
***************************************/
struct VS_OUTPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

/***************************************
頂点シェーダ
***************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float2 tex : TEXCOORD
) {
	VS_OUTPUT Out;

	Out.pos = pos;
	Out.tex = tex;

	return Out;
}

/***************************************
ピクセルシェーダ
***************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	//float y = (int)(In.tex.y * 50.0f) * 0.02f * 20.0f;
	float y = In.tex.y * 50.0f + baseY;
	In.tex.x += (sin(10 * y) + cos(15 * y)) * 0.02f *length;
	
	return tex2D(s0, In.tex);
}

/***************************************
テクニック
***************************************/
technique tech
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
};