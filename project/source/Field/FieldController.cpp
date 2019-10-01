//=====================================
//
//FieldController.cpp
//機能:フィールドコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldController.h"
#include "FieldCursor.h"
#include "FieldGround.h"

#include "../../Framework/Input/input.h"

/**************************************
コンストラクタ
***************************************/
FieldController::FieldController()
{
	//インスタンス作成
	cursor = new FieldCursor();
	ground = new FieldGround();
}

/**************************************
デストラクタ
***************************************/
FieldController::~FieldController()
{
	SAFE_DELETE(cursor);
	SAFE_DELETE(ground);
}

/**************************************
更新処理
***************************************/
void FieldController::Update()
{
	cursor->Update();
}

/**************************************
描画処理
***************************************/
void FieldController::Draw()
{
	ground->Draw();

	//カーソルには透過オブジェクトが含まれるので最後に描画
	cursor->Draw();
}

/**************************************
入力確認処理
***************************************/
void FieldController::CheckInput()
{

}
