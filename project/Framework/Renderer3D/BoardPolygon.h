//=====================================
//
//板ポリゴンヘッダ[BoardPolygon.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOARDPOLYGON_H_
#define _BOARDPOLYGON_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/
class PolygonResource;

/**************************************
クラス定義
***************************************/
class BoardPolygon
{
	friend class PolygonResource;
public:
	//コンストラクタ、デストラクタ
	BoardPolygon();
	~BoardPolygon();

	//描画処理
	void Draw();

	//UV分割設定処理
	void SetTexDiv(const D3DXVECTOR2& div);

	//テクスチャ通し番号設定処理
	void SetTextureIndex(int index);

	//UV座標設定処理
	void SetUV(const D3DXVECTOR2& uv);

protected:
	LPDIRECT3DDEVICE9 pDevice;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	D3DMATERIAL9 material;

	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;

	PolygonResource *resource;
};

#endif