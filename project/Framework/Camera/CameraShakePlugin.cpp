//=====================================
//
//テンプレート処理[CameraShakePlugin.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "CameraShakePlugin.h"
#include "../Math/Easing.h"

/**************************************
マクロ定義
***************************************/

/**************************************
CameraShakePluginコンストラクタ
***************************************/
CameraShakePlugin::CameraShakePlugin()
{
	cntFrame = 0;
	ZeroMemory(&amplitude, sizeof(amplitude));
	duration = 0;
	active = false;
}

/**************************************
CameraShakePlugin更新処理
***************************************/
void CameraShakePlugin::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}

}

/**************************************
CameraShakePlugin反映処理
***************************************/
void CameraShakePlugin::Apply(Transform& work)
{
	if (!active)
		return;

	float t = (float)cntFrame / duration;
	float range = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::OutCirc);

	D3DXVECTOR3 offset;
	offset.x = Math::RandomRange(-range, range) * amplitude.x;
	offset.y = Math::RandomRange(-range, range) * amplitude.y;
	offset.z = Math::RandomRange(-range, range) * amplitude.z;

	work.Move(offset);
}

/**************************************
CameraShakePluginセット処理
***************************************/
void CameraShakePlugin::Set(const D3DXVECTOR3& amplitude, int duration)
{
	cntFrame = 0;
	this->amplitude = amplitude;
	this->duration = duration;
	active = true;
}