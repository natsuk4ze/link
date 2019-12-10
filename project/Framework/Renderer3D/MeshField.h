//=====================================
//
//MeshField.h
//機能:メッシュフィールド
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MeshField : public GameObject
{
public:
	MeshField(int numBlockX, int numBlockZ, float sizeBlockX, float sizeBlockZ);
	virtual ~MeshField();

	void Draw();

	void LoadTexture(const char* path);

private:
	int numBlockX, numBlockZ;
	float sizeBlockX, sizeBlockZ;
	int numVertex;
	int numIndex;
	int numPolygon;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPDIRECT3DTEXTURE9 texture;

	void CreateVertexBuffer();
	void CreateIndexBuffer();
};

#endif