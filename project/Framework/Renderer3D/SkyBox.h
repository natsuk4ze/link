//=====================================
//
//SkyBox.h
//機能:スカイボックスヘッダ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "../../main.h"

#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SkyBox : public GameObject
{
public:
	//面を表すenum
	enum Surface
	{
		Up,
		Back,
		Down,
		Front,
		Left,
		Right,
		Max
	};

	//コンストラクタ、デストラクタ
	SkyBox(const D3DXVECTOR3& size);
	virtual ~SkyBox();

	//描画処理
	virtual void Draw();

	//テクスチャ読み込み
	virtual void LoadTexture(const char* fileName, Surface surface);

protected:
	//テクスチャコンテナ
	std::vector<LPDIRECT3DTEXTURE9> textureContainer;

	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	//頂点バッファ作成処理
	virtual void MakeVertexBuffer(const float width, const float height, const float depth);
};

#endif