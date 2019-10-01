//=====================================
//
//GameInit.h
//機能:ゲームシーン初期化
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEINIT_H_
#define _GAMEINIT_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameInit : public BaseState<GameScene, GameScene::State>
{
public:
	void OnStart(GameScene &entity);
	GameScene::State OnUpdate(GameScene &entity);
};

#endif