//=====================================
//
//ゲームパーティクルマネージャ処理[TestParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TestParticleManager.h"
#include "Game/BlueSpark.h"
#include "../../Framework/Tool/DebugWindow.h"

/**************************************
初期化処理
***************************************/
void TestParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(TestParticle::Max, NULL);
	controllers[TestParticle::BlueSpark] = new Effect::Game::BlueSparkController();
}

/**************************************
更新処理
***************************************/
void TestParticleManager::Update()
{
	Debug::Begin("ParticleTest");

	if (Debug::Button("BlueSpark"))
		Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);

	Debug::End();

	SceneParticleManager::Update();
}
