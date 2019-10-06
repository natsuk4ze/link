//=====================================
//
//フィールドコントローラアイドル状態処理[FieldControllerIdle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldControllerIdle.h"
#include "../../../Framework/Input/input.h"

namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::IdleState::OnStart(FieldController & entity)
	{
		//特に何もしない
	}

	/**************************************
	更新処理
	***************************************/
	FieldController::State FieldController::IdleState::OnUpdate(FieldController & entity)
	{
		State next = State::Idle;

		//Zキーが押されたらBuildへ遷移
		if (Keyboard::GetTrigger(DIK_Z))
		{
			next = State::Build;
		}

		//Xキーが押されたらDevelopへ遷移
		if (Keyboard::GetTrigger(DIK_X))
		{
			next = State::Develop;
		}

		return next;
	}

}