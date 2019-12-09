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
前方宣言
***************************************/
class PolygonResource;
class SpriteEffect;

/**************************************
クラス定義
***************************************/
class BoardPolygon
{
	friend class PolygonResource;
public:
	//コンストラクタ、デストラクタ
	BoardPolygon();
	BoardPolygon(SpriteEffect* effect);
	~BoardPolygon();

	//描画処理
	void Draw(const D3DXMATRIX& mtxWorld);

	//UV分割設定処理
	void SetTexDiv(const D3DXVECTOR2& div);

	//テクスチャ通し番号設定処理
	void SetTextureIndex(int index);

	//ディフューズ設定処理
	void SetDiffuse(const D3DXCOLOR& color);

protected:
	LPDIRECT3DDEVICE9 pDevice;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	PolygonResource *resource;

	SpriteEffect *effect;
};

#endif