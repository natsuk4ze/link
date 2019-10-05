//=====================================
//
// BuildRoad.h
// 機能:道をビルドするステート
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BuildRoad_H_
#define _BuildRoad_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	前方宣言
	***************************************/

	/**************************************
	クラス定義
	***************************************/
	class FieldController::BuildRoadState : public FieldController::ControllerState
	{
	public:
		void OnStart(FieldController& entity);
		State OnUpdate(FieldController& entity);
	};
}
#endif