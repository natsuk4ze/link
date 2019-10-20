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
	State next = State::Idle;

	//入力確認
	entity.field->CheckInput();
	entity.fieldCamera->CheckInput();

	//各オブジェクト更新
	entity.field->Update();

	//イベント更新
	entity.eventController->Update();

	//残り時間が0になったら終了
	if (!entity.field->IsTimeRemaining())
	{
		next = State::Finish;
	}
	//AI発展レベルが最大に到達していたらレベルアップ
	else if (entity.field->ShouldLevelUp())
	{
		next = State::LevelUp;
	}

	return next;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
