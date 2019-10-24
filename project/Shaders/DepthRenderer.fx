//=====================================
//
// DepthRenderer.fx
// 機能:Z値レンダリングシェーダ
// Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
グローバル変数
***************************************/
float4x4 mtxWorld;				//ワールド行列
float4x4 mtxView;				//ビュー行列
float4x4 mtxProjection;			//プロジェクション行列

/**************************************
頂点シェーダ出力構造体
***************************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 depth : TEXCOORD0;
};

/**************************************
深度マップ作成頂点シェーダ
***************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float4 normal : NORMAL,
	float2 tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	//ワールドビュープロジェクション変換
	Out.pos = mul(pos, mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);
	
	//テクスチャ座標を頂点に合わせる
	Out.depth.xy = Out.pos.zw;

	return Out;
}

/**************************************
深度マップ作成ピクセルシェーダ
***************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//Z値算出
	Out = In.depth.x / In.depth.y;
	Out.w = 1.0f;

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