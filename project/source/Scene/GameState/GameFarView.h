//=====================================
//
//GameFarView.h
//機能:全体を遠くから眺めるステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEFARVIEW_H_
#define _GAMEFARVIEW_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameFarView : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);
};

#endif