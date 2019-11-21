//=====================================
//
// ゲームタイトル[GameTitle.cpp]
// 機能：タイtル状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GameTitle.h"

//=====================================
// 入場処理
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	//スコア表示、名前入力などなど
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	//今はとりあえず作っただけ
	State next = State::Title;
	return next;
}
