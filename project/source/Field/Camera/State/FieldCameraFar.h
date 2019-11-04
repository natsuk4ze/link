//=====================================
//
//FieldCameraFar.h
//機能:フィールドカメラ遠景ビュー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMERAFAR_H_
#define _FIELDCAMERAFAR_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera::FieldCameraFar : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);

	static const float CameraLength;
	static const float CameraAngleXZ;
	static const float CameraAngleY;
};
#endif