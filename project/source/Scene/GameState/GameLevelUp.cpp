//=====================================
//
//GameLevelUp.cpp
//機能:ゲームシーンレベルアップステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameLevelUp.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Field/FieldController.h"
#include "../../Event/EventController.h"

/**************************************
入場処理
***************************************/
void GameScene::GameLevelUp::OnStart(GameScene & entity)
{
	// スコアの加算
	entity.field->SetScore();

	//ステップを初期化
	entity.step = Step::WaitLevelPopup;
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameLevelUp::OnUpdate(GameScene & entity)
{
	//ステップ実行
	switch (entity.step)
	{
	case Step::WaitLevelPopup:
		//リンクレベルポップアップを待つ必要がなくなったら演出開始
		if (!entity.field->ShouldWaitPopup())
		{
			// グレードアップ
			entity.gameViewer->SetGradeUp([&]()
			{
				//レベルアップ処理
				entity.OnLevelUp();
				entity.ChangeState(GameScene::State::TransitionOut);
			});

			entity.step = Step::TelopIn;
		}

	default:
		break;
	}


	//オブジェクト更新
	entity.field->UpdateObject();
	entity.eventController->UpdateViewer();
	return State::LevelUp;
}
