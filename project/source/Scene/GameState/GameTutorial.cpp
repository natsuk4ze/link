//=============================================================================
//
// チュートリアルクラス [GameTutorial.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "GameTutorial.h"
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

enum TutorialStep
{
	Road,
	Stock,
	Camera,
	Event,
	Score,
	Over,
};

/**************************************
入場処理
***************************************/
void GameScene::GameTutorial::OnStart(GameScene & entity)
{
	// 初めての入場処理の初期化
	if (!Initialized)
	{
		entity.step = Road;
		FrameCount = 0;
		Initialized = true;
	}

	// カメラの焦点をセット
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	// ゲームシーンで使用するUIの描画をON
	entity.field->SetViewerActive(true);
	entity.gameViewer->SetActive(true);
	GuideViewer::Instance()->SetActive(true);

	entity.remainTime = 30 * 999;
}


/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameTutorial::OnUpdate(GameScene & entity)
{
	switch (entity.step)
	{
	case TutorialStep::Road:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 15)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::LinkRoad);
		}

		// 道を作る操作を確認
		if (entity.field->GetRoadNum() != 0 && !entity.tutorialViewer->isPlaying)
		{
			ClearFlag = true;
		}

		// 条件達成、次の説明に行く
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Stock;
		}

		break;

	case TutorialStep::Stock:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 120)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::Develop);
		}

		// 開拓操作を確認
		if (entity.field->IsDeveloped() && !entity.tutorialViewer->isPlaying)
		{
			ClearFlag = true;
		}

		// 条件達成、次の説明に行く
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Camera;
		}
		break;

	case TutorialStep::Camera:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 60)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::ChangeCamera);
		}

		// カメラの操作を確認
		if (!entity.tutorialViewer->isPlaying)
		{
			if (Keyboard::GetTrigger(DIK_C) || Keyboard::GetTrigger(DIK_SPACE))
			{
				ClearFlag = true;
			}
		}

		// 条件達成、次の説明に行く
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Event;
		}
		break;

	case TutorialStep::Event:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 60)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::EventHappend);
		}

		// イベントの発生を確認
		if (!entity.eventController->IsEmptyEventVec())
		{
			ClearFlag = true;
		}
		
		// 条件達成、次の説明に行く
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Score;
		}
		break;

	case TutorialStep::Score:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 120)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::HighScore);
			ClearFlag = true;
		}

		// 条件達成、次の説明に行く
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Over;
		}

		break;
	case TutorialStep::Over:

		// チュートリアル終了
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			// 初期化
			entity.level = 0;
			entity.InTutorial = false;
			entity.remainTime = 30 * 180;
			Initialized = false;

			// トランジション
			entity.ChangeState(GameScene::State::TransitionOut);
		}
		break;

	default:
		break;
	}

	// チュートリアル中に実績を達成しないために
	RewardController::Instance()->ResetAllRewardData();

	// イベント更新
	entity.eventController->Update();
	entity.eventController->UpdateViewer();

	// フィールド更新
	entity.field->UpdateLogic();
	entity.field->UpdateObject();

	// 操作説明していなければ、入力確認
	if (!entity.tutorialViewer->isPlaying)
	{
		entity.field->CheckInput();

		// 遠景モードへの遷移確認
		if (entity.field->ShouldSwicthCamera())
		{
			entity.ChangeState(State::FarView);
		}
		// カメラを回転させるか
		else if (entity.field->ShouldRotateCamera())
		{
			entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
		}
	}
	else
	{
		// 説明終了
		if (Keyboard::GetTrigger(DIK_Z) || GamePad::GetTrigger(0, BUTTON_C))
		{
			GuideViewer::Instance()->SetActive(true);
			entity.tutorialViewer->isPlaying = false;
		}
	}

	return State::Tutorial;
}
