//=====================================
//
//メッシュコンテナ処理[MeshContainer.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MeshContainer.h"
#include "../Resource/MeshResource.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
MeshContainer::MeshContainer() : 
	mesh(NULL),
	materialNum(0),
	resource(NULL),
	initialized(false)
{

}

/**************************************
デストラクタ
***************************************/
MeshContainer::~MeshContainer()
{
	ReleaseResource();
}

/**************************************
描画処理
***************************************/
void MeshContainer::Draw()
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//マテリアル退避
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < materialNum; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, textures[i]);

		//マテリアル設定
		pDevice->SetMaterial(&materials[i]);

		//描画
		mesh->DrawSubset(i);
	}

	//マテリアル復元
	pDevice->SetMaterial(&matDef);
}

/**************************************
マテリアル数取得処理
***************************************/
UINT MeshContainer::GetMaterialNum()
{
	return materialNum;
}

/**************************************
マテリアル取得処理
***************************************/
void MeshContainer::GetMaterial(UINT index, D3DMATERIAL9& out)
{
	assert(index >= 0 && index < materialNum);
	out = materials[index];
}

/**************************************
マテリアルカラー設定処理
***************************************/
void MeshContainer::SetMaterialColor(const D3DXCOLOR& color, UINT index)
{
	assert(index >= 0 && index < materialNum);

	materials[index].Diffuse = color;

}

/**************************************
マテリアルアルファ設定処理
***************************************/
void MeshContainer::SetMaterialAlpha(float alpha, UINT index)
{
	assert(index >= 0 && index < materialNum);
	materials[index].Diffuse.a = alpha;
}

/**************************************
リソース開放処理
***************************************/
void MeshContainer::ReleaseResource()
{
	SAFE_RELEASE(mesh);

	for (DWORD i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	materials.clear();

	materialNum = 0;

	if (resource != NULL)
	{
		resource->OnRelease();
		resource = NULL;
	}
}
