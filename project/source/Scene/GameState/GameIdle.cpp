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
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/ProfilerCPU.h"

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	ProfilerCPU::Instance()->Begin("Update Event");
	entity.eventController->Update();
	entity.eventController->UpdateViewer();
	ProfilerCPU::Instance()->End("Update Event");

	//入力確認
	entity.field->CheckInput();

	//フィールド更新
	ProfilerCPU::Instance()->Begin("Update Logic");
	entity.field->UpdateLogic();
	ProfilerCPU::Instance()->End("Update Logic");

	ProfilerCPU::Instance()->Begin("Update FieldObject");
	entity.field->UpdateObject();
	ProfilerCPU::Instance()->End("Update FieldObject");

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
	//遠景モードへの遷移確認
	else if (entity.field->ShouldSwicthCamera())
	{
		entity.ChangeState(State::FarView);
	}

	//カメラを回転させるか
	if (entity.field->ShouldRotateCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
	}

	return State::Idle;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
