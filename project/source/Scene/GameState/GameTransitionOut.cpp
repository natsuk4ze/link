//=====================================
//
//GameTransitionOut.cpp
//機能:ゲームのレベルアップ遷移ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameTransitionOut.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"
#include "../../Booth/BoothController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"

/**************************************
入場処理
***************************************/
void GameScene::GameTransitionOut::OnStart(GameScene & entity)
{
	//カメラの状態を遷移
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionOut);

	entity.cntFrame = 0;

	SE::Play(SoundConfig::SEID::Transition, 1.0f);

//gamaeViewerをオフに
	entity.gameViewer->SetActive(false, GameViewer::ViewerNo::ItemStock);
	entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Timer);
	entity.gameViewer->SetActive(false, GameViewer::ViewerNo::Level);
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameTransitionOut::OnUpdate(GameScene & entity)
{
	entity.cntFrame++;

	entity.eventController->UpdateViewer();
	entity.field->UpdateObject();

	//雲パーティクル発生
	if (entity.cntFrame == 45)
	{
		BoothController::Instance()->RotateTable(GameScene::AngleTable[level]);
		GameParticleManager::Instance()->Generate(GameParticle::Cloud, Vector3::Zero);
	}

	//遷移
	if (entity.cntFrame == 90)
	{
		entity.ChangeState(GameScene::TransitionIn);
	}

	return State::TransitionOut;
}
