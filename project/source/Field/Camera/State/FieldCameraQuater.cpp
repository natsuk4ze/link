//=====================================
//
//FieldCameraQuater.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCameraQuater.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Tool/DebugWindow.h"

/**************************************
入場処理
***************************************/
void FieldCamera::FieldCameraQuater::OnStart(FieldCamera & entity)
{
	//パラメータ初期化
	entity.startPosition = entity.transform.GetPosition() - entity.targetObject->GetPosition();
	entity.cntFrame = 0;

	//移動先の座標を設定
	const float CameraAngleXZ = D3DXToRadian(-45.0f);
	const float CameraAngleY = D3DXToRadian(45.0f);
	const float CameraLength = 70.0f;

	entity.goalPosition = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * sinf(CameraAngleXZ)) * CameraLength;

	entity.transform.SetRotation(D3DXVECTOR3(CameraAngleY, CameraAngleXZ, 0.0f));
}

/**************************************
更新処理
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraQuater::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	//イージングで移動
	const float MoveDuration = 30;
	float t = entity.cntFrame / MoveDuration;
	D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

	D3DXVECTOR3 targetPosition = entity.targetObject->GetPosition();
	entity.transform.SetPosition(position + targetPosition);
	entity.transform.LookAt(targetPosition);

	return FieldCamera::QuaterView;
}