//=====================================
//
// アイテムアクター[ItemActor.h]
// 機能：アイテムのアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _ITEMACTOR_H_
#define _ITEMACTOR_H_

#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// 前方宣言
//**************************************
class BoardPolygon;

//**************************************
// クラス定義
//**************************************
class ItemActor :
	public GameObject
{
private:
	// 定数定義
	static const D3DXVECTOR2 ActorSize;		// サイズ
	static const float RotValue;			// 回転速度

	BoardPolygon *polygon;

public:
	ItemActor(const D3DXVECTOR3& pos);
	~ItemActor();

	//板ポリゴン用のリソース作成などの初期化処理
	static void Init();

	void Update();
	void Draw();
	void Rotate(float y);
};
#endif
