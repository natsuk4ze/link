//=====================================
//
//テンプレート処理[BuildRoad.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BuildRoad.h"
#include "../../../Framework/Input/input.h"
#include "../Place/OperatePlaceContainer.h"

namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::BuildRoadState::OnStart(FieldController & entity)
	{
		
	}

	/**************************************
	入場処理
	***************************************/
	FieldController::State FieldController::BuildRoadState::OnUpdate(FieldController & entity)
	{
		return State::BuildRoad;
	}

}