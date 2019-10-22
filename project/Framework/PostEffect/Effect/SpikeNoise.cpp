//=====================================
//
//スパイクノイズ処理[SpikeNoise.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpikeNoise.h"
#include "../../Resource/ResourceManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
SpikeNoise::SpikeNoise(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/EFFECT/SpikeNoise.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	hndlLength = effect->GetParameterByName(0, "length");
	hBaseY = effect->GetParameterByName(0, "baseY");
}

/**************************************
デストラクタ
***************************************/
SpikeNoise::~SpikeNoise()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void SpikeNoise::DrawEffect()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
歪み長さセット処理
***************************************/
void SpikeNoise::SetLength(float length)
{
	effect->SetFloat(hndlLength, length);
	effect->CommitChanges();
}

/**************************************
Y基準点セット処理
***************************************/
void SpikeNoise::SetBaseY(float f)
{
	effect->SetFloat(hBaseY, f);
	effect->CommitChanges();
}