//=====================================
//
// FieldControllerIdle.h
// 機能:フィールドコントローラアイドル状態
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCONTROLLERIDLE_H_
#define _FIELDCONTROLLERIDLE_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	クラス定義
	***************************************/
	class FieldController::IdleState : public BaseState<FieldController, FieldController::State>
	{
		void OnStart(FieldController &entity);
		State OnUpdate(FieldController& entity);
	};
}

#endif