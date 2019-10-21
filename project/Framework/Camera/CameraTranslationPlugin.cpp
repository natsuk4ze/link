//=====================================
//
//カメラ平行移動プラグイン処理[CameraTranslationPluign.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "CameraTranslationPlugin.h"
#include "../Math/Easing.h"

/**************************************
初期化処理
***************************************/
void Camera::TranslationPlugin::Init()
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
void Camera::TranslationPlugin::Update()
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
void Camera::TranslationPlugin::Apply(Camera & camera)
{
	if (state == Idle)
		return;

	float t = (float)cntFrame / durationMove;

	if (state == RestoreBase)
		t = 1.0f - t;

	//注視点から視点へのオフセット値を計算
	D3DXVECTOR3 offsetEye = camera.eyeWork - camera.targetWork;

	//イージングによる移動値を計算
	EaseType type = state == MoveTowards ? EaseType::OutCubic : EaseType::InCubic;
	D3DXVECTOR3 offsetPosition = Easing::EaseValue(t, Vector3::Zero, targetPosition - camera.targetWork, type);

	//注視点を移動
	camera.targetWork += offsetPosition;

	//注視点を基に視点を設定
	camera.eyeWork = camera.targetWork + offsetEye;
}

/**************************************
平行移動セット処理
***************************************/
void Camera::TranslationPlugin::Move(const D3DXVECTOR3 & position, int duration, std::function<void(void)> callback)
{
	targetPosition = position;
	cntFrame = 0;
	durationMove = duration;
	state = MoveTowards;

	this->callback = callback;
}

/**************************************
平行移動復元処理
***************************************/
void Camera::TranslationPlugin::Restore(int duration, std::function<void(void)> callback)
{
	cntFrame = 0;
	durationMove = duration;
	state = RestoreBase;
	
	this->callback = callback;
}
