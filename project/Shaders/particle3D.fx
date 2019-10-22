//=====================================
//
//パーティクルシェーダ[Particle.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/***************************************
グローバル変数
***************************************/
float4x4 mtxView;		//ビュー行列
float4x4 mtxProj;		//プロジェクション行列
float4x4 mtxInvView;	//ビュー逆行列

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
	float4 color : COLOR0;
};

/**************************************************************
頂点シェーダ
***************************************************************/
VS_OUTPUT vsMain(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0,
	float4 mtxWorld1 : TEXCOORD1,
	float4 mtxWorld2 : TEXCOORD2,
	float4 mtxWorld3 : TEXCOORD3,
	float4 mtxWorld4 : TEXCOORD4,
	float2 texUV : TEXCOORD5
) {
	VS_OUTPUT Out;

	Out.pos = float4(pos, 1.0f);

	//world
	float4x4 mtxWorld = {
		mtxWorld1,
		mtxWorld2,
		mtxWorld3,
		mtxWorld4
	};
	Out.pos = mul(Out.pos, mtxWorld);

	//view & projection
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//texUV
	Out.uv = localUV + texUV;

	//Color
	Out.color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return Out;
}

/**************************************************************
ピクセルシェーダ
***************************************************************/
float4 psMain(VS_OUTPUT In) : COLOR0
{
	//テクスチャからカラーを取得
	return tex2D(s0, In.uv) * In.color;
}

/**************************************************************
テクニック
***************************************************************/
technique tech {
	pass p0 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}
};