//=====================================
//
//FieldCameraFar.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCameraFar.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Input/input.h"

/**************************************
staticメンバ
***************************************/
const float FieldCamera::FieldCameraFar::CameraLength = 200.0f;
const float FieldCamera::FieldCameraFar::CameraAngleXZ = D3DXToRadian(90.0f);
const float FieldCamera::FieldCameraFar::CameraAngleY = D3DXToRadian(85.0f);

/**************************************
入場処理
***************************************/
void FieldCamera::FieldCameraFar::OnStart(FieldCamera & entity)
{
	//パラメータ初期化
	entity.startPosition = entity.transform.GetPosition() - entity.targetObject->GetPosition();
	entity.cntFrame = 0;

	//移動先の座標を設定
	entity.goalPosition = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;
}

/**************************************
更新処理
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraFar::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	const float MoveDuration = 30;
	if (entity.cntFrame <= MoveDuration)
	{
		//イージングで移動
		float t = entity.cntFrame / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

		//追従目標に合わせて視点を設定
		entity.transform.SetPosition(position + entity.targetObject->GetPosition());
	}
	else
	{
		//操作で移動
		const float MoveSpeed = 3.0f;

		D3DXVECTOR3 directionMove = {
			Input::GetPressHorizontail(),
			0.0f,
			Input::GetPressVertical()
		};

		D3DXVec3Normalize(&directionMove, &directionMove);

		D3DXVECTOR3 position = entity.target;
		position += directionMove * MoveSpeed;
		position.x = Math::Clamp(0.0f, 50 * 10.0f, position.x);
		position.z = Math::Clamp(-50 * 10.0f, 0.0f, position.z);

		entity.target = position;

		D3DXVECTOR3 eyePosition = D3DXVECTOR3(
			cosf(CameraAngleY) * cosf(CameraAngleXZ),
			sinf(CameraAngleY),
			cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

		entity.transform.SetPosition(position + eyePosition);
	}

	return FieldCamera::FarView;
}
