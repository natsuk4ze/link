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
#include "../../Viewer/GameScene/FieldViewer/OperationExplanationViewer.h"

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
	Exit,
	WaitOver,
	Transition,
};

/**************************************
入場処理
***************************************/
void GameScene::GameTutorial::OnStart(GameScene & entity)
{
	// カメラの焦点をセット
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	// フィールドビューワの操作説明を非表示
	//entity.field->EnableViewOperation(false);

	// ゲームシーンで使用するUIの描画をON
	entity.field->SetViewerActive(true);
	entity.gameViewer->SetActive(true);
	GuideViewer::Instance()->SetActive(true);

	entity.remainTime = 30 * 999;
}

/**************************************
初期化
***************************************/
void GameScene::GameTutorial::Init(GameScene& entity)
{
	entity.step = Road;
	entity.tutorialViewer->Init();
	FrameCount = 0;
	ClearFlag = false;
}

/**************************************
チュートリアルクリア処理
***************************************/
void GameScene::GameTutorial::TutorialClear(GameScene & entity)
{
	entity.tutorialViewer->SetActive(false);
	entity.step = Transition;

	// 初期化
	entity.level = 0;
	entity.InTutorial = false;
	entity.remainTime = 30 * 180;

	// トランジション
	entity.ChangeState(GameScene::State::TransitionOut);
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
		if (entity.field->GetRoadNum() != 0 && !entity.tutorialViewer->GetIsShowTexture())
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

		entity.field->SetOperationExplanation(
			OperationExplanationViewer::OperationID::Z_Build,
			OperationExplanationViewer::OperationID::X_None,
			OperationExplanationViewer::OperationID::C_None,
			OperationExplanationViewer::OperationID::Space_None
		);

		break;

	case TutorialStep::Stock:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 120)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::Develop);
		}

		// 開拓操作を確認
		if (entity.field->IsDeveloped() && !entity.tutorialViewer->GetIsShowTexture())
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

		entity.field->SetOperationExplanation(
			OperationExplanationViewer::OperationID::Z_None,
			OperationExplanationViewer::OperationID::X_Develop,
			OperationExplanationViewer::OperationID::C_None,
			OperationExplanationViewer::OperationID::Space_None
		);

		break;

	case TutorialStep::Camera:

		FrameCount++;

		// 説明を表示する
		if (FrameCount == 60)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::ChangeCamera);
		}

		// カメラの操作を確認
		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			if (Keyboard::GetTrigger(DIK_C) || Keyboard::GetTrigger(DIK_SPACE) ||
				GamePad::GetTrigger(0, BUTTON_A) || GamePad::GetTrigger(0, BUTTON_Z))
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

		entity.field->SetOperationExplanation(
			OperationExplanationViewer::OperationID::Z_None,
			OperationExplanationViewer::OperationID::X_None,
			OperationExplanationViewer::OperationID::C_Change,
			OperationExplanationViewer::OperationID::FarView
		);

		break;

	case TutorialStep::Event:

		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			FrameCount++;

			// 説明を表示する
			if (FrameCount == 60)
			{
				entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::EventHappend);
			}
		}

		// イベントの発生を確認
		// もしくは、イベントマスがないかつ30秒以上経過
		if (!entity.eventController->IsEmptyEventVec() || 
			(FrameCount >= 900 && entity.eventController->GetRemainNum() == 0))
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
			entity.step = TutorialStep::Exit;
		}

		break;

	case TutorialStep::Exit:

		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			ClearFlag = true;
		}

		// 条件達成、次の説明に行く
		if (ClearFlag)
		{
			ClearFlag = false;
			entity.step = TutorialStep::WaitOver;
		}

		break;
	case TutorialStep::WaitOver:

		// チュートリアル終了
		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
			{
				TutorialClear(entity);
			}
		}
		break;

	default:
		break;
	}

	// チュートリアル中に実績を達成しないために
	RewardController::Instance()->ResetAllRewardData();

	if (entity.step != TutorialStep::Transition)
	{
		// 操作説明が表示していなければ、入力確認
		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			// イベント更新
			entity.eventController->Update();
			entity.eventController->UpdateViewer();

			entity.field->CheckInput();

			// フィールド更新
			entity.field->UpdateLogic();
			entity.field->UpdateObject();

			entity.tutorialViewer->SetHelpMessage();

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

			// チュートリアル中止
			if (Keyboard::GetTrigger(DIK_F5) || GamePad::GetTrigger(0, BUTTON_R))
			{
				TutorialClear(entity);
			}
		}
		else if (entity.step != TutorialStep::WaitOver)
		{
			// 説明終了
			if (Keyboard::GetTrigger(DIK_Z) || Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
			{
				GuideViewer::Instance()->SetActive(true);
				entity.tutorialViewer->SetIsShowTexture(false);
			}
		}
	}

	return State::Tutorial;
}
