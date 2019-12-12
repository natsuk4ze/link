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

//=====================================
// 入場処理
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	// シーンチェンジ
	TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop);

	// カメラのモード切替
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// タイトル画面で使用するUIの描画をON
	entity.titleViewer->SetActive(true);
	//entity.titleViewer->InitSelectLogo();

	// 使用しないUIの描画をOFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	//entity.guideViewer->SetActive(false);
	entity.resultViewer->SetActive(false);
	entity.nemeEntryViewer->SetActive(false);

	// タイトルのBGMを開始
	PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Title, 0.1f, 30);

	//モータの角度を初期化
	BoothController::Instance()->RotateTable(GameScene::AngleTable[0]);
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	entity.field->UpdateObject();

	// シーンチェンジ
	if (entity.titleViewer->CheckSceneChange())
	{
		entity.remainTime = 30 * 180;
		entity.titleViewer->SetNextScene(entity);
	}

	State next = State::Title;
	return next;
}
