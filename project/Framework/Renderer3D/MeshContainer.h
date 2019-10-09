//=====================================
//
//メッシュコンテナヘッダ[MeshContainer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MESHCONTAINER_H_
#define _MESHCONTAINER_H_

#include "../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class MeshResource;

/**************************************
クラス定義
***************************************/
class MeshContainer
{
	friend class MeshResource;
public:
	MeshContainer();					//コンストラクタ
	~MeshContainer();					//デストラクタ

	static MeshContainer* Create();
	void Release();

	void Draw();						//モデルを描画

	UINT GetMaterialNum();
	void GetMaterial(UINT index, D3DMATERIAL9& out);
	void SetMaterialColor(const D3DXCOLOR& color, UINT index);
	void SetMaterialAlpha(float alpha, UINT index);

protected:								
	LPD3DXMESH mesh;								//メッシュデータ
	std::vector<D3DMATERIAL9> materials;			//マテリアル情報
	std::vector<LPDIRECT3DTEXTURE9> textures;		//テクスチャ
	DWORD materialNum;								//マテリアル数

private:
	MeshResource * resource;						//リソースの参照元
};

#endif