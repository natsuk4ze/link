//=====================================
//
//PresenDebugController.h
//機能:プレゼン用のデバッグ操作クラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PRESENDEBUGCONTROLLER_H_
#define _PRESENDEBUGCONTROLLER_H_

#include "../../main.h"
#include "../Scene/GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PresenDebugController
{
public:
	PresenDebugController(GameScene* scene);
	~PresenDebugController();

	void Update();

private:
	GameScene *scene;

	void _RaiseMeteorEvent();
	void _ForceLevelUp();
	void _DecreaseLevelAI();
	void _ForceTimeUp();
};

#endif