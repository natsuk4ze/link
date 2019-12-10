//=====================================
//
//フィールドの入力管理処理[FieldInputController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldInput.h"
#include "../../../Framework/Input/input.h"
#include "../Object/FieldCursor.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Tool/DebugWindow.h"

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const int FieldController::FieldInput::InputLongWait = 15;
	const int FieldController::FieldInput::InputShortWait = 4;

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
		if (Keyboard::GetTrigger(DIK_Z) || GamePad::GetTrigger(0, BUTTON_C))
			return true;

		return false;
	}

	/**************************************
	開拓ボタンのトリガー検出
	***************************************/
	bool FieldController::FieldInput::GetDevelopTrigger()
	{
		if (Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_X))
			return true;

		return false;
	}

	/**************************************
	ビルドキャンセル検出
	***************************************/
	bool FieldController::FieldInput::GetBuildCancel()
	{
		//Xキーのトリガー入力を検出したらキャンセル
		if (Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_X))
			return true;

		return false;
	}

	/**************************************
	開拓キャンセル検出
	***************************************/
	bool FieldController::FieldInput::GetDevelopCancel()
	{
		//Zキーのトリガーを検出したらキャンセル
		if (Keyboard::GetTrigger(DIK_Z) || GamePad::GetTrigger(0, BUTTON_C))
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

		//移動方向決定
		D3DXVECTOR3 direction = { Math::Clamp(-1.0f, 1.0f, triggerX + repeatX) , 0.0f,  Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ) };

		//カメラの向きに合わせて移動方向を回転
		D3DXQUATERNION cameraQuaternion = Camera::MainCamera()->GetTransform().GetRotation();
		float cameraAngle = 360.0f - Quaternion::ToEuler(cameraQuaternion).y;
		float rotateAngle = 90.0f * ((int)roundf(cameraAngle) / 90);

		D3DXMATRIX mtxRot;
		D3DXMatrixRotationAxis(&mtxRot, &Vector3::Up, D3DXToRadian(rotateAngle));
		D3DXVec3TransformCoord(&direction, &direction, &mtxRot);

		//カーソルを移動
		entity->cursor->Move((int)roundf(direction.x), (int)roundf(direction.z));

		//現在のステートの更新処理を実行
		State next = entity->state->OnUpdate(*entity);
		if (next != entity->current)
		{
			entity->ChangeState(next);
		}
	}

	/**************************************
	カメラ切り替え入力の検出
	***************************************/
	bool FieldController::FieldInput::CheckSwicthCameraMode()
	{
		//カーソル移動中はfalse
		if (entity->cursor->IsMoving())
			return false;

		if (Keyboard::GetTrigger(DIK_SPACE) || GamePad::GetTrigger(0, BUTTON_Z))
			return true;

		return false;
	}

	/**************************************
	カメラの回転切り替え
	***************************************/
	bool FieldController::FieldInput::CheckRotateCamera()
	{
		//とりあえずCキーで切り替え
		return Keyboard::GetTrigger(DIK_C) || GamePad::GetTrigger(0, BUTTON_A);
	}

	/**************************************
	操作反転処理
	***************************************/
	void FieldController::FieldInput::ReverseOperate(bool isReverse)
	{
		directionInput = isReverse ? -1 : 1;
	}
}


