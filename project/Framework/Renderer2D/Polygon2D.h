//=====================================
//
//ポリゴン2Dヘッダ[Polygon2D.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Polygon2D : public GameObject
{
public:
	Polygon2D();
	virtual ~Polygon2D();

	void Draw();

	void SetSize(float x, float y);
	void SetColor(D3DXCOLOR color);
	void SetUV(float left, float top, float width, float height);

	void LoadTexture(const char* path);

private:
	VERTEX_2D vtxWk[NUM_VERTEX];
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	LPDIRECT3DDEVICE9 pDevice;

	void SetVertex();
};

#endif