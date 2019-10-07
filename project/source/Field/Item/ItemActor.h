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
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class ReverseItemActor;
class ItemActor :
	public BoardPolygon
{
private:
	Transform* transform;
	ReverseItemActor* reverse;				// 裏側用

	// 定数定義
	static const D3DXVECTOR2 ActorSize;		// サイズ
	static const float RotValue;			// 回転速度

public:
	ItemActor(const D3DXVECTOR3& pos);
	~ItemActor();

	void Update();
	void Draw();
	void Rotate(float y);
};

//**************************************
// 裏側用クラス定義
//**************************************
class ReverseItemActor :
	public BoardPolygon
{
private:
	Transform* transform;

public:
	ReverseItemActor(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR2& size);
	~ReverseItemActor();
	void Update();
	void Draw();
	void Rotate(float y);
};

#endif
