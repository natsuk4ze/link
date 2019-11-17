//=====================================
//
//WaterHeightController.cpp
//機能:水の水位コントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WaterHeightController.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
staticメンバ
***************************************/
const int WaterHeightController::AnimationPeriod = 360;
const float WaterHeightController::MaxWaveHeight = 0.015f;

float WaterHeightController::heightWave = 0.0f;
int WaterHeightController::cntWaveAnimation = 0;

/**************************************
水位更新処理
***************************************/
void WaterHeightController::UpdateHeight()
{
	cntWaveAnimation = Math::WrapAround(0, AnimationPeriod, ++cntWaveAnimation);

	float startHeight = (cntWaveAnimation < AnimationPeriod / 2) ? -MaxWaveHeight : MaxWaveHeight;
	float goalHeight = startHeight * -1.0f;
	float t = (cntWaveAnimation < AnimationPeriod / 2) ? cntWaveAnimation / (AnimationPeriod * 0.5f) : (cntWaveAnimation - AnimationPeriod * 0.5f) / (AnimationPeriod * 0.5f);

	heightWave = Easing::EaseValue(t, startHeight, goalHeight, EaseType::InOutBack);
}