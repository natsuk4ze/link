//=====================================
//
//ブルームフィルター処理[BloomFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloomFilter.h"
#include "../../Resource/ResourceManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BloomFilter::BloomFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* Path = "data/EFFECT/BloomFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

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