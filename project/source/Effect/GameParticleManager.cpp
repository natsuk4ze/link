//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "Game/BlueSpark.h"

/**************************************
グローバル変数
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameParticle::Max, NULL);
	controllers[GameParticle::BlueSpark] = new Effect::Game::BlueSparkController();
}
