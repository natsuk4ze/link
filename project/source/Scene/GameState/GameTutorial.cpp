//=============================================================================
//
// チュートリアルクラス [GameTutorial.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "GameTutorial.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Input/input.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"


/**************************************
入場処理
***************************************/
void GameScene::GameTutorial::OnStart(GameScene & entity)
{
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
	//入力確認
	entity.field->CheckInput();

	//フィールド更新
	entity.field->UpdateLogic();
	entity.field->UpdateObject();

	//遠景モードへの遷移確認
	if (entity.field->ShouldSwicthCamera())
	{
		entity.ChangeState(State::FarView);
	}
	//カメラを回転させるか
	else if (entity.field->ShouldRotateCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
	}

	if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		entity.level = 0;
		entity.InTutorial = false;
		entity.remainTime = 30 * 180;

		entity.ChangeState(GameScene::State::TransitionOut);
	}

	return State::Tutorial;
}
