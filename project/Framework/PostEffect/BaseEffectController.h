//=====================================
//
//ベースエフェクトコントローラヘッダ[BaseEffectController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEFFECTCONTROLLER_H_
#define _BASEEFFECTCONTROLLER_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/
class ScreenObject;

/**************************************
クラス定義
***************************************/
class BaseEffectController
{
public:
	BaseEffectController();
	~BaseEffectController();

protected:
	ScreenObject *renderer;
};

#endif