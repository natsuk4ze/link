//=====================================
//
//FieldController.h
//機能:フィールドコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCONTROLLER_H_
#define _FIELDCONTROLLER_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class FieldCursor;
class FieldGround;

/**************************************
クラス定義
***************************************/
class FieldController
{
public:
	FieldController();
	~FieldController();

	void Update();
	void Draw();

	void CheckInput();

private:
	const float PlaceOffset = 10.0f;		//Placeの1マス毎のオフセット値
	const float InitFieldBorder = 25;		//フィールド範囲の初期値

	FieldCursor *cursor;					//カーソル
	FieldGround *ground;					//地面

	int fieldBorder;						//フィールド範囲(マス単位)
};

#endif