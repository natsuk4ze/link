//=====================================
//
//インスタンシングメッシュシェーダ[ModelInstancing.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
*グローバル変数
***************************************/
float4x4 mtxWorld;				//ワールド行列
float4x4 mtxView;				//ビュー行列
float4x4 mtxProjection;			//プロジェクション行列
float4 materialDiffuse;			//マテリアルディフューズ
float4 materialAmbient;			//マテリアルアンビエント
float4 materialSpecular;		//マテリアルスペキュラー

float4 lightDiffuse[3];			//ライトディフューズ
float4 lightAmbient[3];			//ライトアンビエント
float4 lightSpecular[3];		//ライトスペキュラ
float4 lightDirection[3];		//ライト方向

float t;						//変化率

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
	float3 pos0 : POSITION0,
	float3 normal0 : NORMAL0,
	float2 uv0 : TEXCOORD0,
	float3 pos1 : POSITION1,
	float3 normal1 : NORMAL1,
	float2 uv1 : TEXCOORD1)
{
	VS_OUT Out = (VS_OUT)0;

	//頂点変換
	float4 position = float4(pos0 * (1.0f - t) + pos1 * t, 1.0f);
	Out.pos = mul(position, mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//法線をワールド変換
	float3 N = mul(normal0 * (1.0f - t) + normal1 * t, (float3x3)mtxWorld);
	N = normalize(N);

	//UV座標を格納
	if (t < 0.5f)
		Out.uv = uv0;
	else
		Out.uv = uv1;

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