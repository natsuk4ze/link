//=====================================
//
//GameTransition.h
//機能:ゲームのレベルアップ遷移ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMETRANSITION_H_
#define _GAMETRANSITION_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameTransition : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);
};

#endif