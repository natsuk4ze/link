//=====================================
//
//メッシュインスタンシング用のエフェクト処理[InstancingMeshEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "InstancingMeshEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
InstancingMeshRenderer::InstancingMeshRenderer()
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
InstancingMeshRenderer::~InstancingMeshRenderer()
{
	SAFE_RELEASE(effect);
}

/**************************************
ライトとカメラの変更反映処理
***************************************/
void InstancingMeshRenderer::CommitLightAndCamera()
{
	//ビュー、プロジェクション行列設定
	effect->SetMatrix(hMtxView, &mtxView);
	effect->SetMatrix(hMtxProjection, &mtxProjection);

	//ライト情報設定
	effect->SetFloatArray(hLightDirection, (float*)&lightContainer[0].Direction, 3);
	effect->SetFloatArray(hLightDiffuse, (float*)&lightContainer[0].Diffuse, 4);
	effect->SetFloatArray(hLightAmbient, (float*)&lightContainer[0].Ambient, 4);
	effect->SetFloatArray(hLightSpecular, (float*)&lightContainer[0].Specular, 4);
}

/**************************************
マテリアルセット処理
***************************************/
void InstancingMeshRenderer::SetMaterial(const D3DMATERIAL9 & material)
{
	effect->GetFloatArray(hMaterialDiffuse, (float*)&material.Diffuse, 4);
	effect->GetFloatArray(hMaterialAmbient, (float*)&material.Ambient, 4);
	effect->GetFloatArray(hMaterialSpecular, (float*)&material.Specular, 4);
}
