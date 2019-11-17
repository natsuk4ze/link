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
const float WaterHeightController::MaxWaveHeight = -5.0f;
const float WaterHeightController::MinWaveHeight = -7.0f;

float WaterHeightController::heightWave = 0.0f;
int WaterHeightController::cntWaveAnimation = 0;
WaterHeightController::State WaterHeightController::state = WaterHeightController::Riseup;

/**************************************
水位更新処理
***************************************/
void WaterHeightController::UpdateHeight()
{
	cntWaveAnimation = Math::WrapAround(0, AnimationPeriod, ++cntWaveAnimation);

	if (cntWaveAnimation == 0)
	{
		state = (WaterHeightController::State)Math::WrapAround((int)Riseup, (int)Max, (int)state + 1);
	}

	float startHeight = state == Riseup ? MinWaveHeight : MaxWaveHeight;
	float endHeight = state == Riseup ? MaxWaveHeight : MinWaveHeight;
	float t = (float)cntWaveAnimation / AnimationPeriod;

	heightWave = Easing::EaseValue(t, startHeight, endHeight, EaseType::InOutBack);
}
