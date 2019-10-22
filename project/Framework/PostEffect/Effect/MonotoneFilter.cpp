//=====================================
//
//モノトーンフィルタ処理[MonotoneFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MonotoneFilter.h"
#include "../../Math/TMath.h"
#include "../../Resource/ResourceManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
MonotoneFilter::MonotoneFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/Effect/MonotoneFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	effect->SetTechnique("tech");
	hndlPower = effect->GetParameterByName(0, "power");
}

/**************************************
デストラクタ
***************************************/
MonotoneFilter::~MonotoneFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void MonotoneFilter::Draw()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
強さ設定処理
***************************************/
void MonotoneFilter::SetPower(float power)
{
	effect->SetFloat(hndlPower, Math::Clamp(0.0f, 1.0f, power));
	effect->CommitChanges();
}