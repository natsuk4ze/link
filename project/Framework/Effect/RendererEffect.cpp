//=====================================
//
//描画エフェクト処理[RendererEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "RendererEffect.h"

/**************************************
static変数
***************************************/
D3DXMATRIX RendererEffect::mtxView;
D3DXMATRIX RendererEffect::mtxProjection;
std::vector<D3DXVECTOR4> RendererEffect::lightDir;
std::vector<D3DCOLORVALUE> RendererEffect::lightDiffuse;
std::vector<D3DCOLORVALUE> RendererEffect::lightAmbient;
std::vector<D3DCOLORVALUE> RendererEffect::lightSpecular;

/*************************************
ビュー行列設定処理
***************************************/
void RendererEffect::SetView(const D3DXMATRIX & viewMatrix)
{
	mtxView = viewMatrix;
}

/*************************************
プロジェクション行列設定処理
***************************************/
void RendererEffect::SetProjection(const D3DXMATRIX & projectionMatrix)
{
	mtxProjection = projectionMatrix;
}

/*************************************
ライト情報設定処理
***************************************/
void RendererEffect::SetLight(unsigned index, const D3DLIGHT9 & light)
{
	if (lightDir.size() <= index)
	{
		lightDir.resize(index + 1);
		lightDiffuse.resize(index + 1);
		lightAmbient.resize(index + 1);
		lightSpecular.resize(index + 1);
	}

	lightDir[index] = D3DXVECTOR4(light.Direction, 0.0f);
	lightDiffuse[index] = light.Diffuse;
	lightAmbient[index] = light.Ambient;
	lightSpecular[index] = light.Specular;
}

/**************************************
マテリアル情報設定処理
***************************************/
void RendererEffect::SetMaterial(const D3DMATERIAL9 & material)
{
	effect->SetFloatArray(hMatDiffuse, (float*)&material.Diffuse, 4);
	effect->SetFloatArray(hMatAmbient, (float*)&material.Ambient, 4);
	effect->SetFloatArray(hMatSpecular, (float*)&material.Specular, 4);
}

/**************************************
変更反映処理
***************************************/
void RendererEffect::Commit()
{
	effect->SetMatrix(hView, &mtxView);
	effect->SetMatrix(hProjection, &mtxProjection);

	effect->SetVectorArray(hLightDirection, &lightDir[0], lightDir.size());
	effect->SetVectorArray(hLightDiffuse, (D3DXVECTOR4*)&lightDiffuse[0], lightDiffuse.size());
	effect->SetVectorArray(hLightAmbient, (D3DXVECTOR4*)&lightAmbient[0], lightAmbient.size());
	effect->SetVectorArray(hLightSpecular, (D3DXVECTOR4*)&lightSpecular[0], lightSpecular.size());

	effect->CommitChanges();
}

/**************************************
描画開始宣言
***************************************/
void RendererEffect::Begin()
{
	Commit();
	effect->Begin(0, 0);
}

/**************************************
パス開始宣言
***************************************/
void RendererEffect::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
パス終了宣言
***************************************/
void RendererEffect::EndPass()
{
	effect->EndPass();
}

/**************************************
描画終了宣言
***************************************/
void RendererEffect::End()
{
	effect->End();
}
