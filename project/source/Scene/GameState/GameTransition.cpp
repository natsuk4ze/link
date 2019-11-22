//=====================================
//
//GameTransitionOut.cpp
//機能:ゲームのレベルアップ遷移ステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameTransition.h"

#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Effect/GameParticleManager.h"

/**************************************
入場処理
***************************************/
void GameScene::GameTransitionOut::OnStart(GameScene & entity)
{
	//カメラの状態を遷移
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::TransitionOut);
	
	//雲パーティクル発生
	TaskManager::Instance()->CreateDelayedTask(60, [&]()
	{
		GameParticleManager::Instance()->Generate(GameParticle::Cloud, Vector3::Zero);
	});


}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameTransitionOut::OnUpdate(GameScene & entity)
{
	return State::TransitionOut;
}
