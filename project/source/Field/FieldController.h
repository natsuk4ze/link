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
class PlaceModel;

/**************************************
クラス定義
***************************************/
class FieldController
{
public:
	//コンストラクタ、デストラクタ
	FieldController();
	~FieldController();

	//更新、描画処理
	void Update();
	void Draw();

	//入力確認処理
	void CheckInput();

private:
	const float PlaceOffset = 10.0f;		//Placeの1マス毎のオフセット値
	const float InitFieldBorder = 25;		//フィールド範囲の初期値

	FieldCursor *cursor;					//カーソル
	FieldGround *ground;					//地面
	PlaceModel *model;						//3Dモデルマネージャ

	int fieldBorder;						//フィールド範囲(マス単位)
};

#endif