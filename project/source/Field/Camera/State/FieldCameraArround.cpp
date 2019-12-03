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
#include "../../../../Framework/Tool/DebugWindow.h"

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
	entity.cameraAngle = -180.0f;
	const D3DXVECTOR3 startPosition = D3DXVECTOR3(0.0f, 200.0f, -100.0f);
	entity.startPosition = entity.transform->GetPosition();
	entity.cntFrame = 0;
	D3DXVECTOR3 vec = startPosition - Vector3::Zero;
	entity.distance = D3DXVec2Length(&D3DXVECTOR2(vec.x, vec.z));
	entity.transform->LookAt(targetPos);

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
	const int MoveDuration = 60;

	if (entity.cntFrame <= MoveDuration)
	{
		// イージングで移動
		float t = (float)entity.cntFrame / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition + targetPos, EaseType::InOutCirc);
		entity.transform->SetPosition(position);
		entity.transform->LookAt(targetPos);
	}
	else
	{
		// 回転し続ける
		entity.cameraAngle += 1.0f;
		if (entity.cameraAngle >= 180.0f)
		{
			entity.cameraAngle -= 360.0f;
		}
		D3DXVECTOR3 position = entity.transform->GetPosition() - targetPos;
		position.x = entity.distance * sinf(D3DXToRadian(entity.cameraAngle));
		position.z = entity.distance * cosf(D3DXToRadian(entity.cameraAngle));
		entity.transform->SetPosition(position + targetPos);
		entity.transform->LookAt(targetPos);
	}
	return FieldCamera::Arround;
}
