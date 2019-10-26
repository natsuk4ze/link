//=====================================
//
//GamePause.cpp
//機能:ゲーム中断ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GamePause.h"
#include "../../Event/EventController.h"
#include "../../Field/FieldController.h"

/**************************************
入場処理
***************************************/
void GameScene::GamePause::OnStart(GameScene & entity)
{

}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GamePause::OnUpdate(GameScene & entity)
{
	//ロジック以外を更新
	entity.field->UpdateObject();
	entity.eventController->Update();

	//中断解除はイベントハンドラ側に任せる
	return State::Pause;
}
