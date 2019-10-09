//=====================================
//
// UseItem.h
// 機能:アイテム使用ステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _USEITEM_H_
#define _USEITEM_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	クラス定義
	***************************************/
	class FieldController::UseItemState : public FieldController::ControllerState
	{
	public:
		void OnStart(FieldController& entity);
		State OnUpdate(FieldController& entity);
	};
}
#endif