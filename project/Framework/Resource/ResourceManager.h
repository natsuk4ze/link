//=====================================
//
//リソースマネージャヘッダ[ResourceManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "..\..\main.h"
#include "..\Pattern\BaseSingleton.h"
#include <unordered_map>

/**************************************
前方宣言
***************************************/
class MeshContainer;
class BoardPolygon;

class MeshResource;

/**************************************
クラス定義
***************************************/
class ResourceManager : public BaseSingleton<ResourceManager>
{
	friend class BaseSingleton<ResourceManager>;
public:
	//読み込み、解放処理
	void LoadMesh(const char* tag, const char* path);
	void ReleaseMesh(const char* tag);

	void LoadTexture(const char* path);
	void ReleaseTexture(const char* tag);

	void MakePolygon(const char* tag, const char* path, const D3DXVECTOR2& size, const D3DXVECTOR2& uv = D3DXVECTOR2(1.0f, 1.0f));
	void ReleasePolygon(const char* tag);

	//リソース参照処理
	bool GetMesh(const char* tag, MeshContainer*&  pOut);
	bool GetTexture(const char* path, LPDIRECT3DTEXTURE9& pOut);
	bool GetPolygon(const char* tag, BoardPolygon*& pOut);

	//全リソース解放処理
	void AllRelease();

private:
	ResourceManager() {}
	~ResourceManager() {}

	std::unordered_map<std::string, MeshResource*> meshPool;
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> texturePool;
	std::unordered_map<std::string, BoardPolygon*> polygonPool;
};

#endif