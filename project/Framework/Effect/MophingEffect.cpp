//=====================================
//
//MophingEffect.cpp
//機能:モーフィング用エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MophingEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
MophingEffect::MophingEffect()
{	
	//エフェクト読み込み
	ResourceManager::Instance()->GetEffect("data/EFFECT/MophingMesh.cfx", effect);

	//ハンドル取得
	hWorld = effect->GetParameterByName(0, "mtxWorld");
	hView = effect->GetParameterByName(0, "mtxView");
	hProjection = effect->GetParameterByName(0, "mtxProjection");

	hMatDiffuse = effect->GetParameterByName(0, "materialDiffuse");
	hMatAmbient = effect->GetParameterByName(0, "materialAmbient");
	hMatSpecular = effect->GetParameterByName(0, "materialSpecular");

	hLightDirection = effect->GetParameterByName(0, "lightDirection");
	hLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
	hLightAmbient = effect->GetParameterByName(0, "lightAmbient");
	hLightSpecular = effect->GetParameterByName(0, "lightSpecular");

	hTime = effect->GetParameterByName(0, "t");

	hTechnique = effect->GetTechniqueByName("tech");
	effect->SetTechnique(hTechnique);

}

/**************************************
デストラクタ
***************************************/
MophingEffect::~MophingEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
変化割合設定処理
***************************************/
void MophingEffect::SetTime(float t)
{
	t = Math::Clamp(0.0f, 1.0f, t);
	effect->SetFloat(hTime, t);
}

/**************************************
ワールド変換行列設定処理
***************************************/
void MophingEffect::SetWorld(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hWorld, &mtx);
}
