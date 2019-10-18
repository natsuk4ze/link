//=====================================
//
//Template.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameIdle.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	//入力確認
	entity.field->CheckInput();
	entity.fieldCamera->CheckInput();

	//各オブジェクト更新
	entity.field->Update();

	//イベント更新
	entity.eventController->Update();

	//制限時間の更新
	entity.remainTime--;

	return State::Idle;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
