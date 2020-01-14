//=============================================================================
//
// ポーズ画面クラス [GameInterrupt.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "GameInterrupt.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/GameScene/SuspendViewer/SuspendViewer.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tween/Tween.h"


/**************************************
入場処理
***************************************/
void GameScene::GameInterrupt::OnStart(GameScene & entity)
{
	// ビュアーのActive On
	entity.suspendViewer->SetActive(true);

	// ガイド役の画面を非表示
	GuideViewer::Instance()->SetActive(false);

	// Tweenクラスのポーズフラグを設置する
	Tween::SetPause(true);
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameInterrupt::OnUpdate(GameScene & entity)
{
	entity.suspendViewer->Update();

	if (Keyboard::GetTrigger(DIK_Z) || Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
	{
		// いいえ
		if (entity.suspendViewer->GetSelected() == SuspendViewer::Dialog::No)
		{
			// ガイド役の画面を表示
			GuideViewer::Instance()->SetActive(true);

			// ビュアーのActive Off
			entity.suspendViewer->SetActive(false);

			// Tweenクラスのポーズフラグを設置する
			Tween::SetPause(false);

			entity.ChangeState(entity.prevState);
		}
		// はい
		else if (entity.suspendViewer->GetSelected() == SuspendViewer::Dialog::Yes)
		{
			PlayBGM::Instance()->FadeOut();

			// ビュアーのActive Off
			entity.suspendViewer->SetActive(false);

			TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
			{
				// Tweenクラスのポーズフラグを設置する
				Tween::SetPause(false);

				entity.level = 0;
				entity.Clear();
				entity.SetFieldLevel(0);
				entity.field->Load(entity.csvNo);
				entity.ChangeState(State::Title);
			});
		}
	}

	return State::Interrupt;
}
