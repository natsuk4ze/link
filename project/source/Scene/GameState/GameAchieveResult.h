//=====================================
//
//GameAchieveResult.h
//機能:ゲームの実績リザルト画面
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEACHIEVERESULT_H_
#define _GAMEACHIEVERESULT_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
クラス定義
***************************************/
class GameScene::GameAchieveResult : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);

	enum Step
	{
		AchieveViewerIn,
		AchieveInputWait,
		AchieveNameEntryWait,
		AchieveNameEntryFinish,
		AchieveViewerOut,
		Transition
	};

private:
	void TransitionToTitle(GameScene& entity);
};
#endif