//=====================================
//
//FieldCameraFar.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCameraFar.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
入場処理
***************************************/
void FieldCamera::FieldCameraFar::OnStart(FieldCamera & entity)
{
	//パラメータ初期化
	entity.startPosition = entity.transform.GetPosition() - entity.targetObject->GetPosition();
	entity.cntFrame = 0;

	//移動先の座標を設定
	entity.goalPosition = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
}

/**************************************
更新処理
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraFar::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	//イージングで移動
	const float MoveDuration = 30;
	float t = entity.cntFrame / MoveDuration;
	D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

	//追従目標に合わせて視点を設定
	entity.transform.SetPosition(position + entity.targetObject->GetPosition());

	return FieldCamera::FarView;
}
