//=====================================
//
//インスタンシングメッシュシェーダ[ModelInstancing.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
*グローバル変数
***************************************/
float4x4 mtxView;				//ビュー行列
float4x4 mtxProjection;			//プロジェクション行列
float4 materialDiffuse;			//マテリアルディフューズ
float4 materialAmbient;			//マテリアルアンビエント
float4 materialSpecular;		//マテリアルスペキュラー

float4 lightDiffuse[3];			//ライトディフューズ
float4 lightAmbient[3];			//ライトアンビエント
float4 lightSpecular[3];		//ライトスペキュラ
float4 lightDirection[3];		//ライト方向

/**************************************
*テクスチャサンプラー
***************************************/
sampler s0 : register(s0);

/**************************************
*頂点シェーダ出力構造体
***************************************/
struct VS_OUT {
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
	float4 color : COLOR0;
};

/**************************************
*頂点シェーダ
***************************************/
VS_OUT VS(
	float3 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0,
	float4 mtxWorld1 : TEXCOORD1,
	float4 mtxWorld2 : TEXCOORD2,
	float4 mtxWorld3 : TEXCOORD3,
	float4 mtxWorld4 : TEXCOORD4)
{
	VS_OUT Out = (VS_OUT)0;

	float4x4 mtxWorld = { mtxWorld1, mtxWorld2, mtxWorld3, mtxWorld4 };

	//頂点を変換
	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//法線をワールド変換
	float3 N = mul(normal, (float3x3)mtxWorld);
	N = normalize(N);
	
	//UV座標を格納
	Out.uv = uv;

	//ライトによる色を計算
	float4 diffuse = (float4)0;
	float4 ambient = (float4)0;

	for (int i = 0; i < 3; i++)
	{
		float3 L = normalize(-lightDirection[i].xyz);
		diffuse += max(0.0f, dot(L, N)) * lightDiffuse[i];
		ambient += lightAmbient[i];
	}

	Out.color = saturate(diffuse * materialDiffuse + ambient * materialAmbient);

	Out.color.a = 1.0f;

	return Out;
}

/**************************************
*ピクセルシェーダ
***************************************/
float4 PS(VS_OUT In) : COLOR0
{
	return tex2D(s0, In.uv) * In.color;
}

/**************************************
*テクニック
**************************************/
technique tech
{
	pass p0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};