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

	/**************************************
	マテリアル情報設定処理
	***************************************/
	void RiverEffect::SetMaterial(const D3DMATERIAL9 & material)
	{
		effect->SetFloatArray(hMatDiffuse, (float*)&material.Diffuse, 4);
		effect->SetFloatArray(hMatAmbient, (float*)&material.Ambient, 4);
		effect->SetFloatArray(hMatSpecular, (float*)&material.Specular, 4);
	}

	/**************************************
	カメラ情報コミット処理
	***************************************/
	void RiverEffect::CommitCameraParameter()
	{
		effect->SetMatrix(hView, &mtxView);
		effect->SetMatrix(hProjection, &mtxProjection);

		//ライト情報取得
		int numLight = Light::LightMax();
		std::vector<D3DLIGHT9> light(numLight);
		for (int i = 0; i < numLight; i++)
		{
			light[i] = Light::GetData(i);
		}

		//作業領域
		std::vector<D3DXVECTOR4> workDir(numLight);
		std::vector<D3DCOLORVALUE> workColor(numLight);

		//ライト方向設定
		for (int i = 0; i < numLight; i++)
		{
			workDir[i] = D3DXVECTOR4(light[i].Direction, 0.0f);
		}
		effect->SetVectorArray(hLightDirection, &workDir[0], numLight);

		//ライト拡散光設定
		for (int i = 0; i < numLight; i++)
		{
			workColor[i] = light[i].Diffuse;
		}
		effect->SetVectorArray(hLightDiffuse, (D3DXVECTOR4*)&workColor[0], numLight);

		//ライト環境光設定
		for (int i = 0; i < numLight; i++)
		{
			workColor[i] = light[i].Ambient;
		}
		effect->SetVectorArray(hLightAmbient, (D3DXVECTOR4*)&workColor[0], numLight);
	}
}