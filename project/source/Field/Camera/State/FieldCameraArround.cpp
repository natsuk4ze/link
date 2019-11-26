//=====================================
//
// フィールドカメラアラウンド[FieldCameraArround.cpp]
// 機能：フィールドの中心を焦点にして回転するカメラ（タイトル、リザルト用）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "FieldCameraArround.h"
#include "../../FieldConfig.h"
#include "../../../../Framework/Math/Easing.h"

//**************************************
// スタティックメンバ初期化
//**************************************

//=====================================
// 入場
//=====================================
void FieldCamera::FieldCameraArround::OnStart(FieldCamera & entity)
{
	// パラメータ初期化
	const D3DXVECTOR3 targetPos = Field::FieldPosition(25, 25).ConvertToWorldPosition();
	const D3DXVECTOR3 startPosition = D3DXVECTOR3(250.0f, 300.0f, -400.0f);
	entity.startPosition = entity.transform.GetPosition();
	entity.cntFrame = 0;
	entity.cameraAngle = 180.0f;
	entity.transform.LookAt(targetPos);

	// 移動先
	entity.goalPosition = startPosition;
}

//=====================================
// 更新
//=====================================
FieldCamera::Mode FieldCamera::FieldCameraArround::OnUpdate(FieldCamera & entity)
{
	entity.cntFrame++;

	D3DXVECTOR3 targetPos = Field::FieldPosition(25, 25).ConvertToWorldPosition();
	D3DXVECTOR3 vec = targetPos - entity.goalPosition;
	const float Dist = D3DXVec3Length(&vec);
	const int MoveDuration = 60;

	if (entity.cntFrame <= MoveDuration)
	{
		// イージングで移動
		float t = (float)entity.cntFrame / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::InOutCirc);
		entity.transform.SetPosition(position);
		entity.transform.LookAt(targetPos);
	}
	else
	{
		// 回転し続ける
		entity.cameraAngle += 1.5f;
		if (entity.cameraAngle >= 180.0f)
		{
			entity.cameraAngle -= 360.0f;
		}
		D3DXVECTOR3 position = entity.transform.GetPosition() + entity.targetObject->GetPosition();
		position.x = Dist * sinf(D3DXToRadian(entity.cameraAngle));
		position.z = Dist * cosf(D3DXToRadian(entity.cameraAngle));
		entity.transform.SetPosition(position + targetPos);
		entity.transform.LookAt(targetPos);
	}

	return FieldCamera::Arround;
}
