//=====================================
//
//フィールドの入力管理処理[FieldInputController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldInput.h"
#include "../../../Framework/Input/input.h"
#include "../Object/FieldCursor.h"

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const int FieldController::FieldInput::InputLongWait = 15;
	const int FieldController::FieldInput::InputShortWait = 3;

	/**************************************
	コンストラクタ
	***************************************/
	FieldController::FieldInput::FieldInput(FieldController * controller) :
		entity(controller),
		cntInputRepeat(0),
		directionInput(1)
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	FieldController::FieldInput::~FieldInput()
	{
	}

	/**************************************
	ビルドボタンのトリガー検出
	***************************************/
	bool FieldController::FieldInput::GetBuildTrigger()
	{
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}

	/**************************************
	開拓ボタンのトリガー検出
	***************************************/
	bool FieldController::FieldInput::GetDevelopTrigger()
	{
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	ビルドキャンセル検出
	***************************************/
	bool FieldController::FieldInput::GetBuildCancel()
	{
		//Xキーのトリガー入力を検出したらキャンセル
		if (Keyboard::GetTrigger(DIK_X))
			return true;

		return false;
	}

	/**************************************
	開拓キャンセル検出
	***************************************/
	bool FieldController::FieldInput::GetDevelopCancel()
	{
		//Zキーのトリガーを検出したらキャンセル
		if (Keyboard::GetTrigger(DIK_Z))
			return true;

		return false;
	}

	/**************************************
	移動入力確認
	***************************************/
	void FieldController::FieldInput::CheckMoveInput()
	{
		//トリガー確認
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal() * directionInput;
		triggerZ = -Input::GetTriggerVertical() * directionInput;

		//リピート確認
		float repeatX = 0.0f, repeatZ = 0.0f;
		if ((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			cntInputRepeat++;
			if (cntInputRepeat >= InputLongWait && cntInputRepeat % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail() * directionInput;
				repeatZ = -Input::GetPressVertical() * directionInput;
			}
		}
		else
		{
			cntInputRepeat = 0;
		}

		//カーソルを移動
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		entity->cursor->Move((int)x, (int)z);

		//現在のステートの更新処理を実行
		State next = entity->state->OnUpdate(*entity);
		if (next != entity->current)
		{
			entity->ChangeState(next);
		}
	}

	/**************************************
	操作反転処理
	***************************************/
	void FieldController::FieldInput::ReverseOperate(bool isReverse)
	{
		directionInput = isReverse ? -1 : 1;
	}
}


