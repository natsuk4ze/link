//=====================================
//
//MeshResource.cpp
//機能:メッシュリソース
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MeshResource.h"
#include "../Renderer3D/MeshContainer.h"

/**************************************
コンストラクタ
***************************************/
MeshResource::MeshResource(const std::string & path) :
	mesh(NULL),
	materialNum(0),
	cntRef(0)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPD3DXBUFFER tmpMaterial;

	//Xファイル読み込み
	HRESULT res = D3DXLoadMeshFromX(path.c_str(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&tmpMaterial,
		NULL,
		&materialNum,
		&mesh);

	if (res != S_OK)
		return;

	//隣接情報を作成して最適化
	std::vector<DWORD> adjList;
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

	//マテリアルをD3DXMATERIALとして最適化
	materials.resize(materialNum);
	D3DXMATERIAL* matBuffer = (D3DXMATERIAL*)tmpMaterial->GetBufferPointer();
	for (DWORD i = 0; i < materialNum; i++)
	{
		materials[i] = matBuffer[i].MatD3D;
	}

	//テクスチャ読み込み
	textures.resize(materialNum, NULL);
	const std::string DirectoryName = path.substr(0, path.find_last_of('/'));
	for (DWORD i = 0; i < materialNum; i++)
	{
		if (matBuffer[i].pTextureFilename == NULL)
			continue;

		std::string fileName = DirectoryName + "/" + std::string(matBuffer[i].pTextureFilename);
		D3DXCreateTextureFromFile(pDevice, fileName.c_str(), &textures[i]);
	}

	SAFE_RELEASE(tmpMaterial);
}

/**************************************
デストラクタ
***************************************/
MeshResource::~MeshResource()
{
	SAFE_RELEASE(mesh);

	for (auto&& texture : textures)
	{
		SAFE_RELEASE(texture);
	}

	//クローンしたMeshContainerが正常に解放されているか確認
	assert(cntRef == 0);
}

/**************************************
クローン
***************************************/
void MeshResource::Clone(MeshContainer * container)
{
	if (container == NULL)
		return;

	//初期化済みであればリリースする
	if (container->initialized)
	{
		container->ReleaseResource();
	}

	//メッシュの参照を保持
	container->mesh = mesh;
	mesh->AddRef();

	//マテリアルをコピー
	container->materials = materials;

	//テクスチャへの参照を設定
	container->textures = textures;
	for (auto&& texture : textures)
	{
		if (texture == NULL)
			continue;

		texture->AddRef();
	}

	//マテリアル数を保存
	container->materialNum = materialNum;

	//自身をリソースとして登録
	container->resource = this;

	container->initialized = true;

	cntRef++;
}

/**************************************
リリース時の処理
***************************************/
void MeshResource::OnRelease()
{
	cntRef--;
}
