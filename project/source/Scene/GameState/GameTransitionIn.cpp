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

	//アクター切り替え

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
		entity.guideViewer->SetActive(false);
		entity.field->SetViewerActive(false);
		entity.gameViewer->SetGradeTitle(entity.level, [&]()
		{
			entity.guideViewer->SetActive(true);
			entity.field->SetViewerActive(true);
			entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);
			entity.ChangeState(GameScene::Idle);
		});
	}

	return GameScene::TransitionIn;
}
