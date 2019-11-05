//=====================================
//
//メッシュインスタンシング用のエフェクト処理[InstancingMeshEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "InstancingMeshEffect.h"
#include "../Resource/ResourceManager.h"
#include "../Light/Light.h"

/**************************************
コンストラクタ
***************************************/
InstancingMeshEffect::InstancingMeshEffect()
{
	//エフェクト読み込み
	ResourceManager::Instance()->GetEffect("data/EFFECT/InstancingMesh.cfx", effect);

	//ハンドル取得
	hMtxView = effect->GetParameterByName(0, "mtxView");
	hMtxProjection = effect->GetParameterByName(0, "mtxProjection");

	hMaterialDiffuse = effect->GetParameterByName(0, "materialDiffuse");
	hMaterialAmbient = effect->GetParameterByName(0, "materialAmbient");
	hMaterialSpecular = effect->GetParameterByName(0, "materialSpecular");

	hLightDirection = effect->GetParameterByName(0, "lightDirection");
	hLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
	hLightAmbient = effect->GetParameterByName(0, "lightAmbient");
	hLightSpecular = effect->GetParameterByName(0, "lightSpecular");

	hTechnique = effect->GetTechniqueByName("tech");
	effect->SetTechnique(hTechnique);
}

/**************************************
デストラクタ
***************************************/
InstancingMeshEffect::~InstancingMeshEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
ライトとカメラの変更反映処理
***************************************/
void InstancingMeshEffect::CommitCameraParameter()
{
	//ビュー、プロジェクション行列設定
	effect->SetMatrix(hMtxView, &mtxView);
	effect->SetMatrix(hMtxProjection, &mtxProjection);

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

/**************************************
マテリアルセット処理
***************************************/
void InstancingMeshEffect::SetMaterial(const D3DMATERIAL9 & material)
{
	effect->SetFloatArray(hMaterialDiffuse, (float*)&material.Diffuse, 4);
	effect->SetFloatArray(hMaterialAmbient, (float*)&material.Ambient, 4);
	effect->SetFloatArray(hMaterialSpecular, (float*)&material.Specular, 4);
}
