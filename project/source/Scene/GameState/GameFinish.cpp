//=====================================
//
//GameFinish.cpp
//機能:ゲームシーン終了処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameFinish.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Field/FieldController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

/**************************************
入場処理
***************************************/
void GameScene::GameFinish::OnStart(GameScene & entity)
{
	SE::Play(SoundConfig::SEID::TimeUp, 1.0f);
	//タイムアップ表示、表示が終わったらリザルトへ遷移
	entity.gameViewer->SetTimeUp([&]()
	{
		entity.ChangeState(GameScene::State::Result);
	});
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameFinish::OnUpdate(GameScene & entity)
{
	//ロジック以外を更新
	entity.field->UpdateObject();

	State next = State::Finish;
	return next;
}
