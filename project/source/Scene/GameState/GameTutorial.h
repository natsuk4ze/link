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
public:
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;

private:
	int FrameCount = 0;
	// 初めての入場処理の初期化フラグ
	bool Initialized = false;
	// チュートリアル操作が終わるフラグ
	bool ClearFlag = false;
};
#endif