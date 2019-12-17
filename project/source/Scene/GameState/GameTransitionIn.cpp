//=====================================
//
//GameTransitionIn.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameTransitionIn.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../../Framework/Tool/DebugWindow.h"

#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Task/TaskManager.h"

/**************************************
入場処理
***************************************/
void GameScene::GameTransitionIn::OnStart(GameScene & entity)
{
	//全てクリア
	entity.Clear();

	//フィールドレベル切り替え
	entity.SetFieldLevel(entity.level);

	//マップ読み込み
	entity.field->Load();

	//BGMをクロスフェード
	SoundConfig::BGMID bgmID = SoundConfig::GetBgmID(entity.level);
	PlayBGM::Instance()->FadeOut();
	PlayBGM::Instance()->FadeIn(bgmID, 0.3f, 90);

	entity.cntFrame = 0;
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameTransitionIn::OnUpdate(GameScene & entity)
{
	entity.cntFrame++;

	entity.eventController->UpdateViewer();
	entity.field->UpdateObject();

	if (entity.cntFrame == 15)
	{
		//カメラ切り替え
		entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionIn);
	}

	if (entity.cntFrame == 100)
	{
		GuideViewer::Instance()->SetActive(false);
		entity.field->SetViewerActive(false);

		entity.gameViewer->SetGradeTitle(entity.level, [&]()
		{
			GuideViewer::Instance()->SetActive(true);

			entity.field->SetViewerActive(true);
			entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

			entity.gameViewer->SetActive(true, GameViewer::ViewerNo::ItemStock);
			entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Timer);
			entity.gameViewer->SetActive(true, GameViewer::ViewerNo::Level);

			entity.ChangeState(State::Idle);
		});
	}

	return GameScene::TransitionIn;
}
