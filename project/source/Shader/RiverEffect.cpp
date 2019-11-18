//=====================================
//
//RiverEffect.cpp
//機能:RiverActor描画エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RiverEffect.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Light/Light.h"

namespace Field::Actor
{
	/**************************************
	コンストラクタ
	***************************************/
	RiverEffect::RiverEffect()
	{
		//エフェクト
		ResourceManager::Instance()->GetEffect("data/EFFECT/RiverRenderer.cfx", effect);

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

		hTexUV = effect->GetParameterByName(0, "texUV");

		effect->SetTechnique("tech");
	}

	/**************************************
	デストラクタ
	***************************************/
	RiverEffect::~RiverEffect()
	{
		SAFE_RELEASE(effect);
	}

	/**************************************
	ワールド情報設定処理
	***************************************/
	void RiverEffect::SetWorld(const Transform & transform)
	{
		D3DXMATRIX mtx = transform.GetMatrix();
		effect->SetMatrix(hWorld, &mtx);
	}

	/**************************************
	テクスチャUV設定処理
	***************************************/
	void RiverEffect::SetUV(const D3DXVECTOR2 & uv)
	{
		effect->SetFloatArray(hTexUV, (float*)&uv, 2);
	}
}