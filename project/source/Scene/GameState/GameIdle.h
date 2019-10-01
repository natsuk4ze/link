//=====================================
//
//GameIdle.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEIDLE_H_
#define _GAMEIDLE_H_

#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameIdle : public BaseState<GameScene, GameScene::State>
{
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;
};
#endif