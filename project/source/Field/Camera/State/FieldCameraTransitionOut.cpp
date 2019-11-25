//=====================================
//
//FieldCameraTransitionOut.cpp
//機能:レベルアップ遷移時の引きカメラステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCameraTransitionOut.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
staticメンバ
***************************************/
const int FieldCamera::FieldCameraTransitionOut::DurationAccel = 30;
const float FieldCamera::FieldCameraTransitionOut::MaxSpeed = 8.0f;

/**************************************
入場処理
***************************************/
void FieldCamera::FieldCameraTransitionOut::OnStart(FieldCamera & entity)
{
	//パラメータ初期化
	entity.cntFrame = 0;
}

/**************************************
更新処理処理
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraTransitionOut::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	float t = (float)entity.cntFrame / DurationAccel;
	float speed = Easing::EaseValue(t, 0.0f, MaxSpeed, EaseType::InOutCubic);
	entity.transform.Move(Vector3::Up * speed);

	entity.transform.LookAt(entity.targetObject->GetPosition());

	return FieldCamera::Mode::TransitionOut;
}
