//=====================================
//
//FieldCameraRotate.h
//機能:フィールドカメラ回転ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMEARAROTATE_H_
#define _FIELDCAMEARAROTATE_H_

#include "../../../../main.h"
#include "../../../../Framework/Pattern/BaseState.h"
#include "../FieldCamera.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera::FieldCameraRotate : public BaseState<FieldCamera, Mode>
{
public:
	void OnStart(FieldCamera& entity);
	Mode OnUpdate(FieldCamera& entity);
};
#endif