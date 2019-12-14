//=====================================
//
//Template.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameIdle.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	ProfilerCPU::Instance()->Begin("Update Event");
	entity.eventController->Update();
	entity.eventController->UpdateViewer();
	ProfilerCPU::Instance()->End("Update Event");

	//入力確認
	entity.field->CheckInput();

	//フィールド更新
	ProfilerCPU::Instance()->Begin("Update Logic");
	entity.field->UpdateLogic();
	ProfilerCPU::Instance()->End("Update Logic");

	ProfilerCPU::Instance()->Begin("Update FieldObject");
	entity.field->UpdateObject();
	ProfilerCPU::Instance()->End("Update FieldObject");

	//制限時間カウント
	entity.remainTime = Math::Max(0, --entity.remainTime);

	//残り時間が0になったら終了
	if (entity.remainTime == 0)
	{
		if (level == 0)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::City, 0.1f, 30, true);
		}
		else if (level == 1)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::World, 0.1f, 30, true);
		}
		else
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Space, 0.1f, 30, true);
		}
		//entity.field->SetScore();
		entity.field->SetResultPara();
		entity.ChangeState(State::Finish);
	}
	//AI発展レベルが最大に到達していたらレベルアップ
	else if (entity.field->ShouldLevelUp())
	{
		if (level == 0)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::City, 0.1f, 30, true);
			entity.ChangeState(State::LevelUp);
		}
		else if (level == 1)
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::World, 0.1f, 30, true);
			entity.ChangeState(State::LevelUp);
		}
		else
		{
			PlayBGM::Instance()->FadeOut(SoundConfig::BGMID::Space, 0.1f, 30, true);
			entity.ChangeState(State::Result);
		}
	}
	//遠景モードへの遷移確認
	else if (entity.field->ShouldSwicthCamera())
	{
		entity.ChangeState(State::FarView);
	}

	//カメラを回転させるか
	if (entity.field->ShouldRotateCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
	}

	return State::Idle;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{
	// カメラの焦点をセット
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);


	// ゲームシーンで使用するUIの描画をON
	entity.field->SetViewerActive(true);
	entity.gameViewer->SetActive(true);
	GuideViewer::Instance()->SetActive(true);
	//entity.guideViewer->SetActive(true);

	// 使用しないUIの描画をOFF（タイトル、リザルト用など）
	entity.titleViewer->SetActive(false);
}
