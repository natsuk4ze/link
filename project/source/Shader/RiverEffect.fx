//=====================================
//
//[ModelInstancing.fx]
//インスタンシングメッシュシェーダ
//Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
*グローバル変数
***************************************/
float4x4 mtxWorld;
float4x4 mtxView;
float4x4 mtxProjection;
float4 materialDiffuse;
float4 materialAmbient;
float4 materialSpecular;

float4 lightDiffuse[3];
float4 lightAmbient[3];
float4 lightSpecular[3];
float4 lightDirection[3];

float2 texUV;

/**************************************
*テクスチャサンプラ
***************************************/
sampler s0 : register(s0);

/**************************************
*頂点シェーダ出力構造体
***************************************/
struct VS_OUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

/**************************************
*頂点シェーダ
***************************************/
VS_OUT VS(
	float3 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0)
{
	VS_OUT Out = (VS_OUT)0;

	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	Out.uv = uv + texUV;

	float3 N = mul(normal, (float3x3)mtxWorld);
	N = normalize(N);

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
***************************************/
technique tech
{
	pass p0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};