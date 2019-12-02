//=====================================
//
//FieldCameraTransitionIn.cpp
//機能:レベルアップ遷移時のインカメラステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCameraTransitionIn.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
staticメンバ
***************************************/
const float FieldCamera::FieldCameraTransitionIn::CameraInitLength = 10.0f;
const float FieldCamera::FieldCameraTransitionIn::CameraGoalLength = 200.0f;
const float FieldCamera::FieldCameraTransitionIn::CameraAngleXZ = D3DXToRadian(45.0f);
const float FieldCamera::FieldCameraTransitionIn::CameraAngleY = D3DXToRadian(85.0f);

/**************************************
入場処理
***************************************/
void FieldCamera::FieldCameraTransitionIn::OnStart(FieldCamera & entity)
{
	//パラメータ初期化
	entity.cntFrame = 0;
}

/**************************************
更新処理
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraTransitionIn::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	const int MoveDuration = 90;
	float t = (float)entity.cntFrame / MoveDuration;

	float length = Easing::EaseValue(t, CameraInitLength, CameraGoalLength, EaseType::InOutCubic);

	D3DXVECTOR3 offset = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * length;

	D3DXVECTOR3 targetPosition = entity.targetObject->GetPosition();

	entity.transform->SetPosition(targetPosition + offset);
	entity.transform->LookAt(targetPosition);

	return FieldCamera::Mode::TransitionIn;
}
