//=====================================
//
// ゲームタイトル[GameTitle.cpp]
// 機能：タイtル状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GameTitle.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../Viewer/TutorialScene/TutorialViewer.h"
#include "../../Event/EventController.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Serial/SerialWrapper.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"
#include "../../Reward/RewardNotifier.h"
#include "../../Reward/RewardController.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tool/DebugWindow.h"

//=====================================
// 入場処理
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	// シーンチェンジ
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop);

	// 実績のリセット
	// リワードをリセット
	entity.rewardNotifier->ResetAchieved();
	RewardController::Instance()->ResetAllRewardData();

	// カメラのモード切替
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// タイトル画面で使用するUIの描画をON
	//entity.titleViewer->SetActive(true);
	entity.titleViewer->Reset();

	// 使用しないUIの描画をOFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nameEntryViewer->SetActive(false);
	entity.eventController->ClearEventMessage();
	entity.tutorialViewer->isPlaying = false;

	// タイトルのBGMを開始
	PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Title, SoundConfig::VolumeBGM, 30, false);

	//モータの角度を初期化
	BoothController::Instance()->RotateTable(GameScene::AngleTable[0]);

	entity.step = 0;
	entity.InTutorial = false;
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
#if _DEBUG
	static bool SkipTutorial = false;
	Debug::Begin("DebugTool");
	Debug::CheckBox("SkipTutorial", SkipTutorial);
	Debug::End();
#endif

	entity.field->UpdateObject();

	if (entity.step == 1)
	{
		// リワード確認画面からステップを戻す
		if (entity.titleViewer->GetRewardViewer())
		{
			if (Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_X))
			{
				entity.step = 0;
			}
		}

		return State::Title;
	}

	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		TitleViewer::MenuID selected = entity.titleViewer->GetSelectedMenu();

		// シーンチェンジ
		if (selected == TitleViewer::MenuID::StartGame)
		{
			entity.remainTime = 30 * 180;
			entity.step++;

			PlayBGM::Instance()->FadeOut();
			PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.3f, 30, false);

			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				entity.titleViewer->SetActive(false);
#if _DEBUG
				if (!SkipTutorial)
				{
					TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
					{
						entity.level = 0;
						entity.Clear();
						entity.SetTutorial();
						entity.field->Load();

						// カメラの焦点をセット
						entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
						entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

						// シーンチェンジ
						TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
						{
							entity.gameViewer->SetActive(true);

							// グレードタイトル
							entity.gameViewer->SetGradeTitle(0, [&]()
							{
								GuideViewer::Instance()->SetData("張り切って行きましょう", GuideActor::AnimState::TalkingTypeA, SoundConfig::SEID::GameStart);
								entity.ChangeState(GameScene::State::Tutorial);
							});
						});
					});
				}
				else
				{

					TaskManager::Instance()->CreateDelayedTask(30, [&]() 
					{
						entity.titleViewer->SetActive(false);

						entity.gameViewer->SetActive(true);
						entity.gameViewer->SetActive(false, GameViewer::ViewerNo::ItemStock);
						entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Timer);
						entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Level);

						entity.gameViewer->SetGradeTitle(0, [&]()
						{
							entity.gameViewer->SetActive(true, GameViewer::ViewerNo::ItemStock);
							entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Timer);
							entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Level);

							GuideViewer::Instance()->SetData("張り切って行きましょう", GuideActor::AnimState::TalkingTypeA, SoundConfig::SEID::GameStart);
							entity.ChangeState(GameScene::State::Idle);
						});
					});
				}
#else
				TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
				{
					entity.level = 0;
					entity.Clear();
					entity.SetTutorial();
					entity.field->Load();

					// カメラの焦点をセット
					entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
					entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

					// シーンチェンジ
					TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
					{
						entity.gameViewer->SetActive(true);

						// グレードタイトル
						entity.gameViewer->SetGradeTitle(0, [&]()
						{
							GuideViewer::Instance()->SetData("張り切って行きましょう", GuideActor::AnimState::TalkingTypeA, SoundConfig::SEID::GameStart);
							entity.ChangeState(GameScene::State::Tutorial);
						});
					});
				});
#endif
			});
		}
		else if (selected == TitleViewer::MenuID::ViewReward)
		{
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				entity.titleViewer->SetRewardViewer();
				entity.titleViewer->Reset();
			});
		}
		else if (selected == TitleViewer::QuitGame)
		{
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				PostQuitMessage(0);
			});
		}

		if (selected != TitleViewer::None)
		{
			SE::Play(SoundConfig::SEID::Select01, 0.5f);
		}
	}

	State next = State::Title;
	return next;
}
