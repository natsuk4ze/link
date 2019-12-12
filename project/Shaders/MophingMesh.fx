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

float4 nextMaterialDiffuse;		//次のマテリアルディフューズ
float4 nextMaterialAmbient;		//次のマテリアルアンビエント
float4 nextMaterialSpecular;	//次のマテリアルスペキュラ

float4 lightDiffuse[3];			//ライトディフューズ
float4 lightAmbient[3];			//ライトアンビエント
float4 lightSpecular[3];		//ライトスペキュラ
float4 lightDirection[3];		//ライト方向

float t;						//変化率

texture nextTexture;			//変化後のテクスチャ

/**************************************
*テクスチャサンプラー
***************************************/
sampler s0 : register(s0);

sampler nextSampler = sampler_state
{
	Texture = <nextTexture>;
	MagFilter = Linear;
	MinFilter = Linear;
};

/**************************************
*頂点シェーダ出力構造体
***************************************/
struct VS_OUT {
	float4 pos	: POSITION;
	float2 uv1	: TEXCOORD0;
	float2 uv2 : TEXCOORD1;
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
	float3 position = lerp(pos0, pos1, t);
	Out.pos = mul(float4(position, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//法線をワールド変換
	float3 N = mul(lerp(normal0, normal1, t), (float3x3)mtxWorld);
	N = normalize(N);

	//UV座標を格納
	Out.uv1 = uv0;
	Out.uv2 = uv1;

	//ライトによる色を計算
	float4 diffuse = (float4)0;
	float4 ambient = (float4)0;

	for (int i = 0; i < 3; i++)
	{
		float3 L = normalize(-lightDirection[i].xyz);
		diffuse += max(0.0f, dot(L, N)) * lightDiffuse[i];
		ambient += lightAmbient[i];
	}

	float4 matDiffuse = float4(lerp(materialDiffuse.rgb, nextMaterialDiffuse.rgb, t), 1.0f);
	float4 matAmbient = lerp(materialAmbient, nextMaterialAmbient, t);
	Out.color = saturate(diffuse * matDiffuse + ambient * matAmbient);

	Out.color.a = 1.0f;

	return Out;
}

/**************************************
*ピクセルシェーダ
***************************************/
float4 PS(VS_OUT In) : COLOR0
{
	 float4 col0 = tex2D(s0, In.uv1);
	 float4 col1 = tex2D(nextSampler, In.uv2);

	 return lerp(col0, col1, t) * In.color;
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