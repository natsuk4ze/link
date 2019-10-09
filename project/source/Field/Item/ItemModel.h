//=====================================
//
// アイテムモデル[ItemModel.h]
// 機能：フィールド上のアイテムモデル
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _ITEMMODEL_H_
#define _ITEMMODEL_H_

//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class ItemActor;
class ItemModel
{
private:
	ItemActor* actor;

public:
	ItemModel();
	~ItemModel();

	void Update();
	void Draw();
};

#endif
