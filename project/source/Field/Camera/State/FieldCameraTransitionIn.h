//=====================================
//
//FieldCameraTransitionIn.h
//機能:レベルアップ遷移時のインカメラステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMERATRANSITIONIN_H_
#define _FIELDCAMERATRANSITIONIN_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera::FieldCameraTransitionIn : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);

	static const float CameraInitLength;
	static const float CameraGoalLength;
	static const float CameraAngleXZ;
	static const float CameraAngleY;
};

#endif