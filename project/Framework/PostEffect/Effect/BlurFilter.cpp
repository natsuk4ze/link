//=====================================
//
//ブラーフィルター処理[BlurFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BlurFilter.h"
#include "../../Resource/ResourceManager.h"

/**************************************
staticメンバ
***************************************/
const int BlurFilter::SizeTexelArray = 5;

/**************************************
コンストラクタ
***************************************/
BlurFilter::BlurFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/Effect/BlurFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);
	
	texelU = effect->GetParameterByName(0, "texelU");
	texelV = effect->GetParameterByName(0, "texelV");
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
BlurFilter::~BlurFilter()
{
	SAFE_RELEASE(effect);

	offsetTexelU.clear();
	offsetTexelV.clear();
}

/**************************************
描画処理
***************************************/
void BlurFilter::DrawEffect(UINT pass)
{
	effect->SetFloatArray(texelU, &offsetTexelU[0], SizeTexelArray);
	effect->SetFloatArray(texelV, &offsetTexelV[0], SizeTexelArray);
	effect->CommitChanges();

	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}
