//=====================================
//
//FieldCameraTransitionOut.h
//機能:レベルアップ遷移時の引きカメラステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMERATRANSITIONOUT_H_
#define _FIELDCAMERATRANSITIONOUT_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera::FieldCameraTransitionOut : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);

	static const int DurationAccel;
	static const float MaxSpeed;
};

#endif