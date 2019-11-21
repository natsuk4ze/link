//=====================================
//
// ゲームリザルト[GameResult.h]
// 機能：リザルト状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GAMERESULT_H_
#define _GAMERESULT_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

//**************************************
// クラス定義
//**************************************
class GameScene::GameResult : 
	public GameScene::SceneState
{
public:
	State OnUpdate(GameScene& entity);
	void OnStart(GameScene& entity);
};

#endif
