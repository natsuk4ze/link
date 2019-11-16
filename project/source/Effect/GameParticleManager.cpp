//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "Game/BlueSpark.h"
#include "Game/BlueDebris.h"
#include "Game/WhiteSmog.h"
#include "Game/ColorfulDebris.h"
#include "Game/ExplosionFlare.h"
#include "Game/TownExplosion.h"
#include "Game/MeteorExplosion.h"
#include "Game/AngryFace.h"
#include "Game/Darkness.h"
#include "Game/Bubble.h"
#include "Game/MoveTail.h"
#include "Game/SpaceTear.h"
#include "Game/LinkLevelUp.h"
#include "Game\StarRoad.h"

/**************************************
staticメンバ
***************************************/
const float GameParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float GameParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
初期化処理
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameParticle::Max, NULL);
	controllers[GameParticle::BlueSpark] = new Effect::Game::BlueSparkController();
	controllers[GameParticle::BlueDebris] = new Effect::Game::BlueDebrisController();
	controllers[GameParticle::WhiteSmog] = new Effect::Game::WhiteSmogController();
	controllers[GameParticle::ColorfulDebis] = new Effect::Game::ColorfulDebrisController();
	controllers[GameParticle::AngryFace] = new Effect::Game::AngryFaceController();
	controllers[GameParticle::ExplosionFlare] = new Effect::Game::ExplosionFlareController();
	controllers[GameParticle::TownExplosion] = new Effect::Game::TownExplosionController();
	controllers[GameParticle::MeteorExplosion] = new Effect::Game::MeteorExplosionController();
	controllers[GameParticle::Darkness] = new Effect::Game::DarknessController();
	controllers[GameParticle::Bubble] = new Effect::Game::BubbleController();
	controllers[GameParticle::MoveTail] = new Effect::Game::MoveTailController();
	controllers[GameParticle::SpaceTear] = new Effect::Game::SpaceTearController();
	controllers[GameParticle::LinkLevelUp] = new Effect::Game::LinkLevelUpController();
	controllers[GameParticle::StarRoad] = new Effect::Game::StarRoadController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
描画処理
***************************************/
void GameParticleManager::Draw()
{
	SceneParticleManager::Draw();

	Debug::Begin("GameParticle");
	Debug::Text("starroad : %d", controllers[GameParticle::StarRoad]->GetParticleCount());
	Debug::End();
}

/**************************************
シンギュラリティエフェクトセット処理
***************************************/
void GameParticleManager::SetSingularityEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	const D3DXVECTOR3 OffsetPosition = Vector3::Up * 10.0f;

	//BlueDebrisの方の放出時間を少し長めにしているので、BlueDebrisにコールバックを設定する
	controllers[GameParticle::BlueSpark]->SetEmitter(position + OffsetPosition);
	controllers[GameParticle::BlueDebris]->SetEmitter(position + OffsetPosition, callback);
}

/**************************************
町消滅のエフェクトセット処理
***************************************/
void GameParticleManager::SetTownExplosionEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	const D3DXVECTOR3 OffsetPosition = Vector3::Up * 10.0f;

	controllers[GameParticle::ExplosionFlare]->SetEmitter(position + OffsetPosition, callback);
	controllers[GameParticle::TownExplosion]->SetEmitter(position + OffsetPosition);
}

/**************************************
隕石爆発のエフェクトセット処理
***************************************/
void GameParticleManager::SetMeteorExplosionEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::ExplosionFlare]->SetEmitter(position, callback);
	controllers[GameParticle::MeteorExplosion]->SetEmitter(position);
}

/**************************************
怒り顔のエフェクトセット処理
***************************************/
void GameParticleManager::SetAngryFaceEffect(std::function<void(void)> callback)
{
	controllers[GameParticle::AngryFace]->SetEmitter(Vector3::Zero);
}

/**************************************
闇の粒子のエフェクトセット処理
***************************************/
void GameParticleManager::SetDarknessEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::Darkness]->SetEmitter(position, nullptr);
}

/**************************************
アトランティスのエフェクトセット処理
***************************************/
void GameParticleManager::SetAtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::Bubble]->SetEmitter(position, nullptr);
}

/**************************************
移動の軌跡のエフェクトセット処理
***************************************/
BaseEmitter* GameParticleManager::SetMoveTailEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	return controllers[GameParticle::MoveTail]->SetEmitter(position, nullptr);
}