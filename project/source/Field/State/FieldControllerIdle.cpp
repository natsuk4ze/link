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

	}

	/**************************************
	更新処理
	***************************************/
	FieldController::State FieldController::IdleState::OnUpdate(FieldController & entity)
	{
		return State::Idle;
	}

}