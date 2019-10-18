//=====================================
//
//GameFinish.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEFINISH_H_
#define _GAMEFINISH_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameFinish : public GameScene::SceneState
{
public:
	State OnUpdate(GameScene& entity);
	void OnStart(GameScene& entity);
};
#endif