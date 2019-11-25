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

//=====================================
// 入場処理
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	//スコア表示、名前入力などなど
	// リザルト画面で使用するUIの描画をON

	// 使用しないUIの描画をOFF
	entity.field->SetActive(false);
	entity.gameViewer->SetActive(false);
	entity.guideViewer->SetActive(false);

	// リザルト用のUIにAI発展レベルを渡す
	//entity.resultViewer->SetScore(entity.field->GetScore(Field::FieldLevel::City), entity.field->GetScore(Field::FieldLevel::World), entity.field->GetScore(Field::FieldLevel::Space));

}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameResult::OnUpdate(GameScene & entity)
{
	//今はとりあえず作っただけ
	State next = State::Result;
	return next;
}
