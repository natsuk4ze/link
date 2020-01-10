//=============================================================================
//
// ポーズ画面クラス [GameInterrupt.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "GameInterrupt.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Viewer/TutorialScene/TutorialViewer.h"
#include "../../Reward/RewardController.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tween/Tween.h"


/**************************************
入場処理
***************************************/
void GameScene::GameInterrupt::OnStart(GameScene & entity)
{
	// ビュアーのActive On

	// ガイド役の画面を非表示
	GuideViewer::Instance()->SetActive(false);

	Tween::SetPause(true);
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameInterrupt::OnUpdate(GameScene & entity)
{
	if (Keyboard::GetTrigger(DIK_V))
	{
		entity.ChangeState(entity.prevState);

		// ビュアーのActive Off

		// Tweenクラスのポーズフラグを設置する
		Tween::SetPause(false);
	}
	else if (Keyboard::GetTrigger(DIK_2))
	{
		PlayBGM::Instance()->FadeOut();

		TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
		{
			// Tweenクラスのポーズフラグを設置する
			Tween::SetPause(false);

			entity.level = 0;
			entity.Clear();
			entity.SetFieldLevel(0);
			entity.field->Load();
			entity.ChangeState(State::Title);
		});
	}

	return State::Interrupt;
}
