//=====================================
//
// ゲームリザルト[GameResult.cpp]
// 機能：リザルト状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GameResult.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../Field/FieldController.h"

//=====================================
// 入場処理
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	//スコア表示、名前入力などなど
	// カメラのモード切り替え
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// リザルト画面で使用するUIの描画をON
	entity.resultViewer->SetActive(true);

	// 使用しないUIの描画をOFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);

	//宇宙レベルのスコアを保存
	if (level == 2)
	{
		entity.field->SetScore();
	}

	//// リザルト用のUIにAI発展レベルを渡す
	int cityScore = (int)entity.field->GetScore(Field::FieldLevel::City);
	int worldScore = (int)entity.field->GetScore(Field::FieldLevel::World);
	int spaceScore = (int)entity.field->GetScore(Field::FieldLevel::Space);
	entity.resultViewer->ReceiveParam(cityScore, worldScore, spaceScore);
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameResult::OnUpdate(GameScene & entity)
{
	//とりあえずエンターが押されたらタイトルへ戻る
	if (Keyboard::GetTrigger(DIK_RETURN))
	{
		TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
		{
			entity.level = 0;
			entity.Clear();
			entity.SetFieldLevel(0);
			entity.field->Load();
			entity.ChangeState(State::Title);
		});
	}

	return State::Result;
}
