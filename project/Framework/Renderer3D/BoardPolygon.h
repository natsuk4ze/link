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

/**************************************
クラス定義
***************************************/
class BoardPolygon
{
	friend class ResourceManager;
public:
	//コンストラクタ、デストラクタ
	BoardPolygon();
	~BoardPolygon();

	//描画処理
	void Draw();

	//テクスチャ読み込み処理
	void LoadTexture(const char* path);

	//サイズ設定処理
	void SetSize(const D3DXVECTOR2& size);

	//UV分割設定処理
	void SetTexDiv(const D3DXVECTOR2& div);

	//テクスチャ通し番号設定処理
	void SetTextureIndex(int index);

	void AddRef();

protected:
	LPDIRECT3DDEVICE9 pDevice;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	D3DMATERIAL9 material;

	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;

	UINT cntReference;
};

#endif