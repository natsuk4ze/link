//=====================================
//
//Template.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameIdle.h"
#include "../../Field/FieldController.h"

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	entity.field->Update();

	return State::Idle;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
