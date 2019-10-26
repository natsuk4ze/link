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
	entity.field->UpdateLogic();
	entity.field->UpdateObject();

	//イベント更新
	entity.eventController->Update();

	//制限時間カウント
	entity.remainTime = Math::Max(0, --entity.remainTime);

	//残り時間が0になったら終了
	if (entity.remainTime == 0)
	{
		entity.ChangeState(State::Finish);
	}
	//AI発展レベルが最大に到達していたらレベルアップ
	else if (entity.field->ShouldLevelUp())
	{
		entity.ChangeState(State::LevelUp);
	}

	return State::Idle;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
