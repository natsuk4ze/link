//=====================================
//
//メッシュコンテナ処理[MeshContainer.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MeshContainer.h"
#include <stdio.h>
#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
Create関数
***************************************/
MeshContainer* MeshContainer::Create()
{
	MeshContainer* ptr = new MeshContainer();
	return ptr;
}

/**************************************
Release関数
***************************************/
void MeshContainer::Release()
{
	cntReference--;
	if (cntReference == 0)
	{
		delete this;
	}
}

/**************************************
AddRef関数
***************************************/
void MeshContainer::AddRef()
{
	cntReference++;
}

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
MeshContainer::MeshContainer() :
	cntReference(0)
{
	cntReference++;
}

/**************************************
デストラクタ
***************************************/
MeshContainer::~MeshContainer()
{
	SAFE_RELEASE(mesh);

	for (DWORD i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}
}

/**************************************
ファイル読み込み処理
***************************************/
HRESULT MeshContainer::Load(const char* filePath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPD3DXBUFFER tmpMaterial;

	//Xファイル読み込み
	HRESULT res = D3DXLoadMeshFromX(filePath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&tmpMaterial,
		NULL,
		&materialNum,
		&mesh);

	if (res != S_OK)
	{
		return res;
	}

	//メッシュの隣接情報を作成して最適化
	std::vector<DWORD> adjList;
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

	//マテリアルをD3DXMATERIALとして複写
	materials = (D3DMATERIAL9*)malloc(sizeof(D3DMATERIAL9) * materialNum);
	D3DXMATERIAL* matBuffer = (D3DXMATERIAL*)tmpMaterial->GetBufferPointer();
	for (DWORD i = 0; i < materialNum; i++)
	{
		materials[i] = matBuffer[i].MatD3D;
	}

	//テクスチャ読み込み
	textures = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * materialNum);
	ZeroMemory(textures, sizeof(LPDIRECT3DTEXTURE9) * materialNum);
	char directoryPath[_MAX_DIR];
	size_t length = strlen(filePath);

	for (DWORD i = length - 1; i >= 0; i--)
	{
		if (filePath[i] == '/')
		{
			strncpy(directoryPath, filePath, i + 1);
			directoryPath[i + 1] = '\0';
			break;
		}
	}

	for (DWORD i = 0; i < materialNum; i++)
	{
		if (matBuffer[i].pTextureFilename == NULL)
			continue;

		//テクスチャ名をwcharに変換
		char fileName[1024];
		ZeroMemory(fileName, sizeof(fileName));
		strcpy(fileName, matBuffer[i].pTextureFilename);

		//テクスチャファイルパスを作成
		char textureFile[1024];
		ZeroMemory(textureFile, sizeof(textureFile));
		strcat(textureFile, directoryPath);
		strcat(textureFile, fileName);

		//ロード
		D3DXCreateTextureFromFile(pDevice, (LPSTR)textureFile, &textures[i]);
	}

	SAFE_RELEASE(tmpMaterial);

	return res;
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