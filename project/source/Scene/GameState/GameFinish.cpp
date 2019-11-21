//=====================================
//
//GameFinish.cpp
//機能:ゲームシーン終了処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameFinish.h"
#include "../../Field/Camera/FieldCamera.h"

/**************************************
入場処理
***************************************/
void GameScene::GameFinish::OnStart(GameScene & entity)
{
	//スコアの保存とか終了テロップの再生とかをやる
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameFinish::OnUpdate(GameScene & entity)
{
	//今はとりあえず作っただけ
	State next = State::Finish;
	return next;
}
