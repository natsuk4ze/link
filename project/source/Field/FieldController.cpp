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

namespace FieldModel
{
	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder)
	{
		//インスタンス作成
		cursor = new FieldCursor();
		ground = new FieldGround();

		//カーソルの移動範囲を初期化
		cursor->SetBorder(fieldBorder * PlaceOffset, fieldBorder * PlaceOffset);
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
		float x = 0.0f, z = 0.0f;

		//X軸方向の入力をX軸移動として取得
		x = Input::GetRepeatHorizontal();

		//X軸軸入力が無かったらY軸入力を確認（斜め移動を禁止するため）
		if (x == 0.0f)
		{
			z = Input::GetRepeatVertical();
		}

		//カーソルを移動
		cursor->Move(D3DXVECTOR3(x, 0.0f, z) * PlaceOffset);
	}
}