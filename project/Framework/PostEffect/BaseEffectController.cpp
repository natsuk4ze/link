//=====================================
//
//テンプレート処理[BaseEffectController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BaseEffectController.h"
#include "ScreenObject.h"

/**************************************
コンストラクタ
***************************************/
BaseEffectController::BaseEffectController()
{
	renderer = new ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************
デストラクタ
***************************************/
BaseEffectController::~BaseEffectController()
{
	SAFE_DELETE(renderer);
}
