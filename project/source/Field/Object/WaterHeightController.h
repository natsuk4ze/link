//=====================================
//
//WaterHeightController.h
//機能:水の水位コントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WATERHEIGHTCONTROLLER_H_
#define _WATERHEIGHTCONTROLLER_H_

#include "../../../main.h"

/**************************************
クラス定義
***************************************/
class WaterHeightController
{
public:
	//高さ更新処理
	static void UpdateHeight();

	//高さ取得処理
	static float GetHeight()
	{
		return heightWave;
	}

private:
	static const int AnimationPeriod;
	static const float MaxWaveHeight;

	static float heightWave;
	static int cntWaveAnimation;
};
#endif