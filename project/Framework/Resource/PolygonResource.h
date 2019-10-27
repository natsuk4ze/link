//=====================================
//
//PolygonResource.h
//機能:ポリゴンリソース
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POLYGONRESOURCE_H_
#define _POLYGONRESOURCE_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class BoardPolygon;

/**************************************
クラス定義
***************************************/
class PolygonResource
{
public:
	PolygonResource(const D3DXVECTOR2& size, const D3DXVECTOR2& uv = { 0.0f, 0.0f}, const char* texturePath = nullptr);
	~PolygonResource();

	void Clone(BoardPolygon* entity);
	void OnRelease();

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	unsigned cntRef;
};

#endif