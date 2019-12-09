//=====================================
//
//[RiverRenderer.fx]
//RiverActor描画シェーダ
//Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
*グローバル変数
***************************************/
float4x4 mtxWorld;
float4x4 mtxView;
float4x4 mtxProj;
float4 diffuse;
float time;
texture Lumine;

/**************************************
*テクスチャサンプラ
***************************************/
sampler s0 : register(s0);
sampler LumineSampler = sampler_state
{
	Texture = <Lumine>;
	MagFilter = Linear;
	MinFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

/**************************************
*頂点シェーダ出力構造体
***************************************/
struct VS_OUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

/**************************************
*頂点シェーダ
***************************************/
VS_OUT VS(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0)
{
	VS_OUT Out = (VS_OUT)0;

	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	Out.uv = localUV;

	return Out;
}

/**************************************
*ピクセルシェーダ
***************************************/
float4 PS(VS_OUT In) : COLOR0
{
	float4 color = tex2D(s0, In.uv) * diffuse;
	
	In.uv /= 50.0f;
	float alpha = tex2D(LumineSampler, In.uv + float2(time, time)).r;
	color.a *= alpha;

	return color;
}

/**************************************
*テクニック
***************************************/
technique tech
{
	pass p0
	{
		ALPHABLENDENABLE = true;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};