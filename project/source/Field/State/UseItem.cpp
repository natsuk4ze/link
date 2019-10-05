//=====================================
//
//アイテム使用処理[UseItem.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "UseItem.h"
#include "../../../Framework/Input/input.h"
namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::UseItemState::OnStart(FieldController & entity)
	{

	}

	/**************************************
	更新処理
	***************************************/
	FieldController::State FieldController::UseItemState::OnUpdate(FieldController & entity)
	{
		return State::UseItem;
	}
}