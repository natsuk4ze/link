//=====================================
//
//パーティクルシェーダ[Particle.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/***************************************
グローバル変数
***************************************/
float4x4 mtxWorld;		//ワールド変換行列
float4x4 mtxView;		//ビュー行列
float4x4 mtxProj;		//プロジェクション行列
float4x4 mtxScreenProj;	//2D用のプロジェクション行列

float2 texUV;			//テクスチャのUV座標

float4 diffuse;			//マテリアルのディフューズ

/**************************************************************
テクスチャサンプラー（0番にSetTextureしたテクスチャを使用する
***************************************************************/
sampler s0 : register(s0);

/**************************************************************
頂点シェーダ出力構造体
***************************************************************/
struct VS_OUTPUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

/**************************************************************
頂点シェーダ(3D用)
***************************************************************/
VS_OUTPUT VS_3D(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	Out.uv = localUV + texUV;

	return Out;
}

/**************************************************************
頂点シェーダ(2D用)
***************************************************************/
VS_OUTPUT VS_2D(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.pos = mul(float4(pos, 0.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxScreenProj);

	Out.uv = localUV + texUV;

	return Out;
}

/**************************************************************
ピクセルシェーダ
***************************************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	return tex2D(s0, In.uv) * diffuse;
}

/**************************************************************
テクニック
***************************************************************/
technique tech
{
	pass P0 {
		ALPHABLENDENABLE = true;
		VertexShader = compile vs_2_0 VS_3D();
		PixelShader = compile ps_2_0 PS();
	}

	pass P1 {
		ALPHABLENDENABLE = true;
		VertexShader = compile vs_2_0 VS_2D();
		PixelShader = compile ps_2_0 PS();
	}
};