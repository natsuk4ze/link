//=====================================
//
//クロスブラーフィルター処理[CrossBlurFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CrossBlurFilter.h"
#include "../../Resource/ResourceManager.h"

/**************************************
マクロ定義
***************************************/
const int CrossBlurFilter::SizeTexelArray = 2;

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
CrossBlurFilter::CrossBlurFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/EFFECT/CrossBlur.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	hTexelU = effect->GetParameterByName(0, "texelU");
	hTexelV = effect->GetParameterByName(0, "texelV");
	effect->SetTechnique("tech");

	offsetTexelU.resize(SizeTexelArray);
	offsetTexelV.resize(SizeTexelArray);

	for (int i = 0; i < SizeTexelArray; i++)
	{
		offsetTexelU[i] = 1.0f / width * (i + 1);
		offsetTexelV[i] = 1.0f / height * (i + 1);
	}
}

/**************************************
デストラクタ
***************************************/
CrossBlurFilter::~CrossBlurFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void CrossBlurFilter::DrawEffect(UINT pass)
{
	effect->SetFloatArray(hTexelU, &offsetTexelU[0], SizeTexelArray);
	effect->SetFloatArray(hTexelV, &offsetTexelV[0], SizeTexelArray);
	effect->CommitChanges();

	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}