//=====================================
//
//リソースマネージャ処理[ResourceManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResourceManager.h"
#include "../Renderer3D/MeshContainer.h"
#include "../Renderer3D/BoardPolygon.h"

#include "MeshResource.h"
#include "PolygonResource.h"

/**************************************
マクロ定義
***************************************/

/**************************************
メッシュ読み込み処理
***************************************/
void ResourceManager::LoadMesh(const char* tag, const char* path)
{
	std::string tagStr = tag;

	//タグの重複確認
	if (meshPool.count(tagStr) != 0)
		SAFE_DELETE(meshPool[tagStr]);

	//メッシュリソースを生成
	meshPool[tagStr] = new MeshResource(path);
}

/**************************************
メッシュ解放処理
***************************************/
void ResourceManager::ReleaseMesh(const char* tag)
{
	std::string tagStr = tag;

	//タグの登録確認
	if (meshPool.count(tagStr) == 0)
		return;

	//メッシュコンテナを削除
	SAFE_DELETE(meshPool[tagStr]);
	meshPool.erase(tagStr);
}

/**************************************
メッシュ取得処理
***************************************/
bool ResourceManager::GetMesh(const char* tag, MeshContainer* pOut)
{
	std::string tagStr = std::string(tag);

	//登録確認
	if (meshPool.count(tagStr) == 0)
		return false;

	//メッシュへの参照を格納
	meshPool[tagStr]->Clone(pOut);
	return true;
}

/**************************************
テクスチャ読み込み処理
***************************************/
void ResourceManager::LoadTexture(const char* path)
{
	std::string tagStr = path;

	//重複確認
	if (texturePool.count(tagStr) != 0)
		return;

	//読み込み
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, path, &texturePool[tagStr]);
}

/**************************************
テクスチャ解放処理
***************************************/
void ResourceManager::ReleaseTexture(const char* tag)
{
	std::string tagStr = tag;

	//登録確認
	if (texturePool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(texturePool[tagStr]);
}

/**************************************
テクスチャ参照処理
***************************************/
bool ResourceManager::GetTexture(const char* path, LPDIRECT3DTEXTURE9& pOut)
{
	std::string tagStr = path;

	//登録確認
	if (texturePool.count(tagStr) == 0)
	{
		LoadTexture(path);
	}

	pOut = texturePool[tagStr];

	if(pOut != NULL)
		pOut->AddRef();

	return true;
}

/**************************************
板ポリゴン作成処理
***************************************/
void ResourceManager::MakePolygon(const char* tag, const char* path, const D3DXVECTOR2& size, const D3DXVECTOR2& uv)
{
	std::string tagStr = std::string(tag);

	//登録確認
	if (polygonPool.count(tagStr) != 0)
		return;

	//BoardPolygonクラスを生成して登録
	PolygonResource *ptr = new PolygonResource(size, uv, path);
	polygonPool[tagStr] = ptr;
}

/**************************************
板ポリゴン解放処理
***************************************/
void ResourceManager::ReleasePolygon(const char* tag)
{
	std::string tagStr = std::string(tag);

	//登録確認
	if (polygonPool.count(tagStr) == 0)
		return;

	SAFE_DELETE(polygonPool[tagStr]);
}

/**************************************
エフェクト読み込み処理
***************************************/
void ResourceManager::LoadEffect(const char * path)
{
	std::string tagStr = std::string(path);

	//重複確認
	if (effectPool.count(tagStr) != 0)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, path, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effectPool[tagStr], 0);
}

/**************************************
エフェクト解放処理
***************************************/
void ResourceManager::ReleaseEffect(const char * path)
{
	std::string tagStr = std::string(path);

	//登録確認
	if (effectPool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(effectPool[tagStr]);
}

/**************************************
板ポリゴン参照処理
***************************************/
bool ResourceManager::GetPolygon(const char* tag, BoardPolygon* pOut)
{
	std::string tagStr = std::string(tag);

	//登録確認
	if (polygonPool.count(tagStr) == 0)
		return false;

	polygonPool[tagStr]->Clone(pOut);
	return true;
}

/**************************************
エフェクト取得処理
***************************************/
bool ResourceManager::GetEffect(const char * path, LPD3DXEFFECT & pOut)
{
	std::string tagStr = std::string(path);

	//登録確認
	if (effectPool.count(tagStr) == 0)
		LoadEffect(path);

	pOut = effectPool[tagStr];
	pOut->AddRef();
	return true;
}

/**************************************
全リソース解放処理
***************************************/
void ResourceManager::AllRelease()
{
	for (auto& pair : meshPool)
	{
		SAFE_DELETE(pair.second);
	}
	meshPool.clear();

	for (auto& pair : texturePool)
	{
		SAFE_RELEASE(pair.second);
	}
	texturePool.clear();

	for (auto& pair : polygonPool)
	{
		SAFE_DELETE(pair.second);
	}
	polygonPool.clear();

	for (auto&& pair : effectPool)
	{
		SAFE_RELEASE(pair.second);
	}
	effectPool.clear();
}