//=====================================
//
//ゲームパーティクルマネージャ処理[TestParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TestParticleManager.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "Game/BlueSpark.h"
#include "Game/BlueDebris.h"
#include "Game/WhiteSmog.h"
#include "Game/TownExplosion.h"
#include "Game/ExplosionFlare.h"
#include "Game/AngryFace.h"
#include "Game/MeteorExplosion.h"
#include "Game/MeteorFire.h"
#include "Game/Darkness.h"
#include "Game/Bubble.h"
#include "Game/WaterSmog.h"
#include "Game/MoveTail.h"
#include "Game/LinkLevelUp.h"

/**************************************
初期化処理
***************************************/
void TestParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(TestParticle::Max, NULL);
	controllers[TestParticle::BlueSpark] = new Effect::Game::BlueSparkController();
	controllers[TestParticle::BlueDebris] = new Effect::Game::BlueDebrisController();
	controllers[TestParticle::WhiteSmog] = new Effect::Game::WhiteSmogController();
	controllers[TestParticle::ExplosionFlare] = new Effect::Game::ExplosionFlareController();
	controllers[TestParticle::AngryFace] = new Effect::Game::AngryFaceController();
	controllers[TestParticle::TownExplosion] = new Effect::Game::TownExplosionController();
	controllers[TestParticle::MeteorExplosion] = new Effect::Game::MeteorExplosionController();
	controllers[TestParticle::MeteorFire] = new Effect::Game::MeteorFireController();
	controllers[TestParticle::Darkness] = new Effect::Game::DarknessController();
	controllers[TestParticle::Bubble] = new Effect::Game::BubbleController();
	controllers[TestParticle::WaterSmog] = new Effect::Game::WaterSmogController();
	controllers[TestParticle::MoveTail] = new Effect::Game::MoveTailController();
	controllers[TestParticle::LinkLevelUp] = new Effect::Game::LinkLevelUpController();
}

/**************************************
更新処理
***************************************/
void TestParticleManager::Update()
{
	Debug::Begin("ParticleTest");

	if (Debug::Button("BlueSpark"))
		Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);
	else if (Debug::Button("BlueDebris"))
		Generate(TestParticle::BlueDebris, Vector3::Up * 10.0f);
	else if (Debug::Button("WhiteSmog"))
		Generate(TestParticle::WhiteSmog, Vector3::Up * 10.0f);
	else if (Debug::Button("TownExplosion"))
		Generate(TestParticle::TownExplosion, Vector3::Up * 20.0f);
	else if (Debug::Button("ExplosionFlare"))
		Generate(TestParticle::ExplosionFlare, Vector3::Up);
	else if (Debug::Button("AngryFace"))
		Generate(TestParticle::AngryFace, Vector3::Zero);
	else if (Debug::Button("MeteorExplosion"))
		Generate(TestParticle::MeteorExplosion, Vector3::Up * 10.0f);
	else if (Debug::Button("MeteorFire"))
		Generate(TestParticle::MeteorFire, Vector3::Up * 20.0f);
	else if (Debug::Button("Darkness"))
		Generate(TestParticle::Darkness, Vector3::Zero);
	else if (Debug::Button("Bubble"))
		Generate(TestParticle::Bubble, Vector3::Zero);
	else if (Debug::Button("WaterSmog"))
		Generate(TestParticle::WaterSmog, Vector3::Zero);
	else if (Debug::Button("LinkLevelUp"))
		Generate(TestParticle::LinkLevelUp, { SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });

	Debug::NewLine();

	if (Debug::Button("BlueSparkDeblis"))
	{
		Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);
		Generate(TestParticle::BlueDebris, Vector3::Up * 10.0f);
	}
	else if (Debug::Button("TownExplosion & Flare"))
	{
		Generate(TestParticle::ExplosionFlare, Vector3::Up);
		Generate(TestParticle::TownExplosion, Vector3::Up * 20.0f);
	}
	else if (Debug::Button("MeteorExplosion & Flare"))
	{
		Generate(TestParticle::ExplosionFlare, Vector3::Up* 10.0f);
		Generate(TestParticle::MeteorExplosion, Vector3::Up * 10.0f);
	}

	Debug::NewLine();

	if (Debug::Button("Callback Test"))
	{
		Generate(TestParticle::WhiteSmog, Vector3::Up * 10.0f, [&]()
		{
			this->Generate(TestParticle::BlueSpark, Vector3::Up * 10.0f);
		});
	}

	Debug::End();

	SceneParticleManager::Update();
}

/**************************************
描画処理
***************************************/
void TestParticleManager::Draw()
{
	SceneParticleManager::Draw();

	Debug::Begin("PartcileProfile");
	for (unsigned i = 0; i < controllers.size(); i++)
	{
		Debug::Text("particle[%d] : %d", i, controllers[i]->GetParticleCount());
	}
	Debug::End();
}
