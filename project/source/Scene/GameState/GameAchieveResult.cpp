//=====================================
//
//GameAchieveResult.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameAchieveResult.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Reward/RewardController.h"
#include "../../Field/FieldController.h"

#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Input/input.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

#include <functional>

/**************************************
入場処理
***************************************/
void GameScene::GameAchieveResult::OnStart(GameScene & entity)
{
	Debug::Log("AchieveResult is Started");

	auto rewardContainer = RewardController::Instance()->IsAllAchieved();
	for (int i = 0; i < RewardConfig::Max; i++)
	{
		rewardContainer.push_back(RewardConfig::Type(i));
	}

	//実績がなかったらタイトルへ遷移
	if (rewardContainer.empty())
	{
		TransitionToTitle(entity);
	}
	//あったら表示開始
	else
	{
		entity.resultViewer->SetAchieveViewerActive(true);
		entity.resultViewer->SetAchiveViewer(rewardContainer, [&]()
		{
			entity.step++;
		});
		entity.step = Step::AchieveViewerIn;
	}
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameAchieveResult::OnUpdate(GameScene & entity)
{
	//ロジック以外を更新
	entity.field->UpdateObject();

	switch (entity.step)
	{
	case Step::AchieveViewerIn:

		break;

	case Step::AchieveInputWait:
		if (Keyboard::GetTrigger(DIK_RETURN))
		{
			//初達成の実績があったらネームエントリー
			if (RewardController::Instance()->FindFirstAchieved())
			{
				entity.step = Step::AchieveInputWait;
			}
			//なかったらタイトルへ
			else
			{
				TransitionToTitle(entity);
			}
		}
	}

	return State::AchieveResult;
}

/**************************************
タイトルへ遷移
***************************************/
void GameScene::GameAchieveResult::TransitionToTitle(GameScene& entity)
{
	PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Result, 0.1f, 30, true);

	TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	{
		entity.level = 0;
		entity.Clear();
		entity.SetFieldLevel(0);
		entity.field->Load();
		entity.ChangeState(State::Title);
	});

	entity.step = Transition;
}
