//=====================================
//
//ショックブラーシェーダ[ShockBlur.fx]
//Author:GP12B332 21 立花雄太
//
//=====================================

/***************************************
グローバル変数
***************************************/
float2 centerTexel;		//中心となるテクセル
float blurPower;		//ブラー強さ
float tU;				//1テクセルの大きさ（X方向）
float tV;				//1テクセルの大きさ（Y方向）

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
	float2 tex : TEXCOORD0
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
	float4 Color[10];

	//ブラー方向
	float2 dir = centerTexel - In.tex;

	//距離を計算
	float len = length(dir);

	//正規化し1テクセル分にする
	dir = normalize(dir) * float2(tU, tV);

	//ボケ具合を計算
	dir *= blurPower * len;

	//合成
	Color[0] = tex2D(s0, In.tex) * 0.19f;
	Color[1] = tex2D(s0, In.tex + dir) * 0.17f;
	Color[2] = tex2D(s0, In.tex + dir * 2.0f) * 0.15f;
	Color[3] = tex2D(s0, In.tex + dir * 3.0f) * 0.13f;
	Color[4] = tex2D(s0, In.tex + dir * 4.0f) * 0.11f;
	Color[5] = tex2D(s0, In.tex + dir * 5.0f) * 0.09f;
	Color[6] = tex2D(s0, In.tex + dir * 6.0f) * 0.07f;
	Color[7] = tex2D(s0, In.tex + dir * 7.0f) * 0.05f;
	Color[8] = tex2D(s0, In.tex + dir * 8.0f) * 0.03f;
	Color[9] = tex2D(s0, In.tex + dir * 9.0f) * 0.01f;

	return Color[0] + Color[1] + Color[2] + Color[3] + Color[4] + Color[5] + Color[6] + Color[7] + Color[8] + Color[9];
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