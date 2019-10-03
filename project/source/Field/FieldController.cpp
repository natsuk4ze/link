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
#include "../FieldObject/PlaceModel.h"
#include "Place\FieldPlaceContainer.h"

#include "../../Framework/Input/input.h"

namespace Field
{
	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		inputRepeatCnt(0)
	{
		//インスタンス作成
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();

		model = new ::PlaceModel();

		//カーソルの移動範囲を初期化
		cursor->SetBorder(fieldBorder / 2, fieldBorder / 2);
	}

	/**************************************
	デストラクタ
	***************************************/
	FieldController::~FieldController()
	{
		SAFE_DELETE(cursor);
		SAFE_DELETE(ground);
		SAFE_DELETE(placeContainer);
	}

	/**************************************
	更新処理
	***************************************/
	void FieldController::Update()
	{
		cursor->Update();
		placeContainer->Update();
		model->Update();
	}

	/**************************************
	描画処理
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		placeContainer->Draw();
		model->Draw();

		//カーソルには透過オブジェクトが含まれるので最後に描画
		cursor->Draw();
	}

	/**************************************
	入力確認処理
	TODO：読み込むデータを選択できるようにする
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");
	}

	/**************************************
	入力確認処理
	***************************************/
	void FieldController::CheckInput()
	{
		//トリガー確認
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal();
		triggerZ = Input::GetTriggerVertical();

		//リピート確認
		float repeatX = 0.0f, repeatZ = 0.0f;
		if((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			inputRepeatCnt++;
			if (inputRepeatCnt >= InputLongWait && inputRepeatCnt % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail();
				repeatZ = Input::GetPressVertical();
			}
		}
		else
		{
			inputRepeatCnt = 0;
		}

		//カーソルを移動
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		cursor->Move((int)x, (int)z);
	}

	/**************************************
	カーソル取得処理
	***************************************/
	GameObject * FieldController::GetFieldCursor()
	{
		return cursor;
	}
}