//=====================================
//
//FieldCameraTranslationPlugin.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCameraTranslationPlugin.h"
#include "../../../../Framework/Math/Easing.h"

/**************************************
初期化処理
***************************************/
void FieldCameraTranslationPlugin::Init()
{
	cntFrame = 0;
	durationMove = 0;
	targetPosition = Vector3::Zero;
	state = Idle;
	callback = nullptr;
}

/**************************************
更新処理
***************************************/
void FieldCameraTranslationPlugin::Update()
{
	if (cntFrame >= durationMove || state == Idle)
		return;

	cntFrame++;

	if (cntFrame == durationMove && callback != nullptr)
		callback();
}

/**************************************
適用処理
***************************************/
void FieldCameraTranslationPlugin::Apply(Transform& work)
{
	if (state == Idle)
		return;

	float t = (float)cntFrame / durationMove;

	if (state == RestoreBase)
		t = 1.0f - t;

	//イージングによる移動値を計算
	EaseType type = state == MoveTowards ? EaseType::OutCubic : EaseType::InCubic;
	D3DXVECTOR3 offsetPosition = Easing::EaseValue(t, Vector3::Zero, targetPosition - work.GetPosition(), type);

	work.Move(offsetPosition);
}

/**************************************
平行移動セット処理
***************************************/
void FieldCameraTranslationPlugin::Move(const D3DXVECTOR3 & position, int duration, std::function<void(void)> callback)
{
	D3DXVECTOR3 offset = D3DXVECTOR3(
		cosf(FieldCamera::CameraAngleY) * cosf(FieldCamera::InitCameraAngle),
		sinf(FieldCamera::CameraAngleY),
		cosf(FieldCamera::CameraAngleY) * sinf(FieldCamera::InitCameraAngle)) * FieldCamera::LengthFromTarget;

	targetPosition = position + offset;
	cntFrame = 0;
	durationMove = duration;
	state = MoveTowards;

	this->callback = callback;
}

/**************************************
平行移動復元処理
***************************************/
void FieldCameraTranslationPlugin::Restore(int duration, std::function<void(void)> callback)
{
	cntFrame = 0;
	durationMove = duration;
	state = RestoreBase;

	this->callback = callback;
}
