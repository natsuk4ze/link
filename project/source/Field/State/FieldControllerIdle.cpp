//=====================================
//
//フィールドコントローラアイドル状態処理[FieldControllerIdle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldControllerIdle.h"
#include "../FieldInputController.h"

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
		if (GetBuildTrigger())
		{
			next = State::Build;
		}

		//Xキーが押されたらDevelopへ遷移
		if (GetDevelopTrigger())
		{
			next = State::Develop;
		}

		return next;
	}

}