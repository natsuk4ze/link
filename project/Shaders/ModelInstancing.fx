//=====================================
//
//モデルインスタンシングシェーダ[ModelInstancing.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/**************************************
*グローバル変数
***************************************/
float4x4 mtxView;				//ビュー行列
float4x4 mtxProj;				//プロジェクション行列
float4 matDiffuse;				//マテリアルディフューズ
float4 matAmbient;				//マテリアルアンビエント

float4 lightDiffuse[3];			//ライトディフューズ配列
float4 lightAmbient[3];			//ライトアンビエント配列
float4 lightDir[3];				//ライト方向配列

float amplifier = 1.0f;			//増幅率

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
	float3 normal	: TEXCOORD1;
};

/**************************************
*頂点シェーダ
***************************************/
VS_OUT vsMain(
	float3 pos		: POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0,
	float3 worldPos : TEXCOORD1,
	float3 worldRot : TEXCOORD2,
	float3 worldScl : TEXCOORD3
) {
	VS_OUT Out;

	Out.pos = float4(pos, 1.0f);
	Out.normal = normal;

	//スケール変換
	float4x4 mtx = {
		worldScl.x, 0.0f, 0.0f, 0.0f,
		0.0f, worldScl.y, 0.0f, 0.0f,
		0.0f, 0.0f, worldScl.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
	Out.pos = mul(mtx, Out.pos);

	//X軸回転
	mtx = float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(worldRot.x), -sin(worldRot.x), 0.0f,
		0.0f, sin(worldRot.x), cos(worldRot.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);
	Out.normal = mul(mtx, float4(Out.normal, 1.0f)).xyz;

	//Y軸回転
	mtx = float4x4(
		cos(worldRot.y), 0.0f, sin(worldRot.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(worldRot.y), 0.0f, cos(worldRot.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);
	Out.normal = mul(mtx, float4(Out.normal, 1.0f)).xyz;

	//Z軸回転
	mtx = float4x4(
		cos(worldRot.z), -sin(worldRot.z), 0.0f, 0.0f,
		sin(worldRot.z), cos(worldRot.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);
	Out.normal = mul(mtx, float4(Out.normal, 1.0f)).xyz;

	//平行移動
	mtx = float4x4(
		1.0f, 0.0f, 0.0f, worldPos.x,
		0.0f, 1.0f, 0.0f, worldPos.y,
		0.0f, 0.0f, 1.0f, worldPos.z,
		0.0f, 0.0f, 0.0f, 1.0f );
	Out.pos = mul(mtx, Out.pos);

	//ビュー変換、プロジェクション変換
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//UV座標格納
	Out.uv = uv;

	return Out;
}

/**************************************
*ピクセルシェーダ（パス0用） ※テクスチャディフューズを使用する
***************************************/
float4 psMain0(VS_OUT In) : COLOR0
{
	//各光源の反射率を計算
	float power0 = dot(In.normal, lightDir[0].xyz) * amplifier;
	float power1 = dot(In.normal, lightDir[1].xyz) * amplifier;
	float power2 = dot(In.normal, lightDir[2].xyz) * amplifier;

	//テクスチャから色を取得
	float4 RC = tex2D(s0, In.uv);

	//並行光源の計算
	float4 color = RC * max(lightDiffuse[0] * power0, 0.0f);
	color += RC * max(lightDiffuse[1] * power1, 0.0f);
	color += RC * max(lightDiffuse[2] * power2, 0.0f);

	//環境光の計算
	color += lightAmbient[0] * matAmbient;
	color += lightAmbient[1] * matAmbient;
	color += lightAmbient[2] * matAmbient;

	//不透明に設定
	color.a = 1.0f;

	return  color;
}

/**************************************
*ピクセルシェーダ（パス1用） ※マテリアルディフューズを使用する
***************************************/
float4 psMain1(VS_OUT In) : COLOR0
{
	//各光源の反射率を計算
	float power0 = dot(In.normal, lightDir[0].xyz) * amplifier;
	float power1 = dot(In.normal, lightDir[1].xyz) * amplifier;
	float power2 = dot(In.normal, lightDir[2].xyz) * amplifier;

	//マテリアルディフューズを取得
	float4 RC = matDiffuse;

	//並行光源の計算
	float4 color = RC * max(lightDiffuse[0] * power0, 0.0f);
	color += RC * max(lightDiffuse[1] * power1, 0.0f);
	color += RC * max(lightDiffuse[2] * power2, 0.0f);

	//環境光の計算
	color += lightAmbient[0] * matAmbient;
	color += lightAmbient[1] * matAmbient;
	color += lightAmbient[2] * matAmbient;

	//不透明に設定
	color.a = 1.0f;

	return  color;
}

/**************************************
*テクニック
***************************************/
technique tech
{
	//テクスチャディフューズ使用版
	pass p0 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain0();
	}

	//マテリアルディフューズ使用版
	pass p1 {
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain1();
	}
}