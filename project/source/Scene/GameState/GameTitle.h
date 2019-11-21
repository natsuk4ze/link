//=====================================
//
// ゲームタイトル[GameTitle.h]
// 機能：タイtル状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GAMETITLE_H_
#define _GAMETITLE_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

//**************************************
// クラス定義
//**************************************
class GameScene::GameTitle :
	public GameScene::SceneState
{
public:
	State OnUpdate(GameScene& entity);
	void OnStart(GameScene& entity);
};

#endif
