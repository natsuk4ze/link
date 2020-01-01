//=============================================================================
//
// チュートリアルクラス [GameTutorial.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _GameTutorial_H_
#define _GameTutorial_H_

#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameTutorial : public BaseState<GameScene, GameScene::State>
{
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;
};
#endif