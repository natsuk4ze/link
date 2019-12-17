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
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Serial/SerialWrapper.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"
#include "../../Reward/RewardNotifier.h"
#include "../../Reward/RewardController.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../../Framework/Task/TaskManager.h"

//=====================================
// 入場処理
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	// シーンチェンジ
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop);

	//実績のリセット
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
	//entity.guideViewer->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nameEntryViewer->SetActive(false);

	// タイトルのBGMを開始
	PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Title, 0.1f, 30);

	//モータの角度を初期化
	BoothController::Instance()->RotateTable(GameScene::AngleTable[0]);

	entity.step = 0;
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	entity.field->UpdateObject();

	if (entity.step == 1)
		return State::Title;

	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		SE::Play(SoundConfig::SEID::Select01, 0.5f);
		entity.step++;

		TitleViewer::MenuID selected = entity.titleViewer->GetSelectedMenu();

		// シーンチェンジ
		if (selected == TitleViewer::MenuID::StartGame)
		{
			entity.remainTime = 30 * 180;

			PlayBGM::Instance()->FadeOut();
			PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::City, 0.3f, 30);

			TaskManager::Instance()->CreateDelayedTask(30, [&]() {

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

					entity.ChangeState(GameScene::State::Idle);
					entity.step = 0;
				});
			});
		}
		else if (selected == TitleViewer::MenuID::ViewReward)
		{
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				entity.titleViewer->SetRewardViewer();
				entity.titleViewer->Reset();
				entity.step = 0;
			});
		}
		else if (selected == TitleViewer::QuitGame)
		{
			TaskManager::Instance()->CreateDelayedTask(30, [&]() {
				PostQuitMessage(0);
			});
		}
	}

	State next = State::Title;
	return next;
}
