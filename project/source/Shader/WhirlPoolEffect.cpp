//=====================================
//
//WhirlPoolEffect.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WhirlPoolEffect.h"
#include "../../Framework/Resource/ResourceManager.h"

namespace Field::Actor
{
	/**************************************	
	コンストラクタ
	***************************************/
	WhirlPoolEffect::WhirlPoolEffect()
	{
		//エフェクト読み込み
		ResourceManager::Instance()->GetEffect("data/EFFECT/WhirlPoolRenderer.cfx", effect);

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

		hTime = effect->GetParameterByName(0, "time");

		effect->SetTechnique("tech");
	}

	/**************************************
	デストラクタ
	***************************************/
	WhirlPoolEffect::~WhirlPoolEffect()
	{
		SAFE_RELEASE(effect);
	}

	/**************************************
	ワールド変換行列設定処理
	***************************************/
	void WhirlPoolEffect::SetWorld(const Transform & transform)
	{
		D3DXMATRIX mtx = transform.GetMatrix();
		effect->SetMatrix(hWorld, &mtx);
	}

	/**************************************
	経過時間設定処理
	***************************************/
	void WhirlPoolEffect::SetTime(float t)
	{
		effect->SetFloat(hTime, t);
	}
}