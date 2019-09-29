//=====================================
//
//ブルームフィルター処理[BloomFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloomFilter.h"

/**************************************
マクロ定義
***************************************/
#define EFFECTFILE_BLOOMFILTER_PATH		"PostEffect/BloomFilter.fx"
#define PRECOMPILE_BLOOMFILTER_PATH		"data/EFFECT/BloomFilter.cfx"

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BloomFilter::BloomFilter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_BLOOMFILTER_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_BLOOMFILTER_PATH, 0, 0, 0, 0, &effect, 0);

	hThrethold = effect->GetParameterByName(0, "threthold");
	hBloomPower = effect->GetParameterByName(0, "bloomPower");
}

/**************************************
デストラクタ
***************************************/
BloomFilter::~BloomFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void BloomFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
しきい値設定処理
***************************************/
void BloomFilter::SetThrethold(float threthold)
{
	effect->SetFloat(hThrethold, threthold);
	effect->CommitChanges();
}

/**************************************
ゲイン設定処理
***************************************/
void BloomFilter::SetBloomPower(float power)
{
	effect->SetFloat(hBloomPower, power);
	effect->CommitChanges();
}