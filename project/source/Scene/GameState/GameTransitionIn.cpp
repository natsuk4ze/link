//=====================================
//
//GameTransitionIn.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameTransitionIn.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"
#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../../Framework/Tool/DebugWindow.h"

/**************************************
入場処理
***************************************/
void GameScene::GameTransitionIn::OnStart(GameScene & entity)
{
	LARGE_INTEGER start, end;

	//全てクリア
	entity.Clear();

	//フィールドレベル切り替え
	entity.SetFieldLevel(entity.level);

	//マップ読み込み
	start = ProfilerCPU::GetCounter();
	entity.field->Load();
	end = ProfilerCPU::GetCounter();

	Debug::Log("Load Map : %f", ProfilerCPU::CalcElapsed(start, end));

	//アクター切り替え


	//カメラ切り替え
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionIn);

	entity.cntFrame = 0;
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameTransitionIn::OnUpdate(GameScene & entity)
{
	entity.cntFrame++;

	if (entity.cntFrame == 90)
	{
		entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);
		entity.ChangeState(GameScene::Idle);
	}

	return GameScene::TransitionIn;
}
