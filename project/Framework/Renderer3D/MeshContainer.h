//=====================================
//
//メッシュコンテナヘッダ[MeshContainer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MESHCONTAINER_H_
#define _MESHCONTAINER_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class MeshContainer
{
	friend class ResourceManager;
public:
	static MeshContainer* Create();
	void Release();

	HRESULT Load(const char* filePath);	//Xファイルの読み込み
	void Draw();						//モデルを描画

	UINT GetMaterialNum();
	void GetMaterial(UINT index, D3DMATERIAL9& out);
	void SetMaterialColor(const D3DXCOLOR& color, UINT index);
	void SetMaterialAlpha(float alpha, UINT index);

	void AddRef();

protected:								
	MeshContainer();					//コンストラクタ
	~MeshContainer();					//デストラクタ


	LPD3DXMESH mesh;					//メッシュデータ
	D3DMATERIAL9* materials;			//マテリアル情報
	LPDIRECT3DTEXTURE9 *textures;		//テクスチャ
	DWORD materialNum;					//マテリアル数

	UINT cntReference;
};

#endif