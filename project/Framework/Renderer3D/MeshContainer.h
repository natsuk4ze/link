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
class RendererEffect;

/**************************************
クラス定義
***************************************/
class MeshContainer
{
	friend class MeshResource;
public:
	MeshContainer();								//コンストラクタ
	virtual ~MeshContainer();						//デストラクタ

	virtual void ReleaseResource();					//リソース解放処理

	virtual void Draw();							//モデルを描画
	virtual void Draw(RendererEffect& effect);		//モデルを描画（シェーダ使用)

	virtual UINT GetMaterialNum();
	virtual void GetMaterial(UINT index, D3DMATERIAL9& out);
	virtual void SetMaterialColor(const D3DXCOLOR& color, UINT index);
	virtual void SetMaterialAlpha(float alpha, UINT index);

protected:								
	LPD3DXMESH mesh;								//メッシュデータ
	std::vector<D3DMATERIAL9> materials;			//マテリアル情報
	std::vector<LPDIRECT3DTEXTURE9> textures;		//テクスチャ
	DWORD materialNum;								//マテリアル数

private:
	MeshResource * resource;						//リソースの参照元
	bool initialized;								//メッシュが初期化済みかどうか

};

#endif