//=====================================
//
//GamePause.h
//機能:ゲーム中断ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

#include "../../../main.h"
#include "../GameScene.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GamePause : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);
};

#endif