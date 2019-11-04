//=====================================
//
//GameFarView.cpp
//機能:ゲームを遠くから眺めるステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameFarView.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Input/input.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"

/**************************************
入場処理
***************************************/
void GameScene::GameFarView::OnStart(GameScene & entity)
{
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::FarView);
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameFarView::OnUpdate(GameScene & entity)
{
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
	//視点変更ボタンが押されたらIdleモードへ遷移
	else if (entity.field->ShouldSwicthCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);
		entity.ChangeState(State::Idle);
	}

	return State::FarView;
}
