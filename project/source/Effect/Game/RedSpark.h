//=============================================================================
//
// 赤いスパークエフェクトクラス [RedSpark.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RedSpark_H_
#define _RedSpark_H_

#include "../../../main.h"
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"
#include <vector>

namespace Effect::Game
{
	/**************************************
	RedSparkクラス
	***************************************/
	class RedSpark : public BaseViewerDrawer
	{
	private:

	public:
		RedSpark();
		void Update();

	};

	/**************************************
	RedSparkControllerクラス
	***************************************/
	class RedSparkController
	{
	private:
		std::vector<RedSpark*> SparkEffect;

	public:
		RedSparkController();
	};
}
#endif