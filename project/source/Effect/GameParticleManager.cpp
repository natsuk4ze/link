//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"

#include "Game/BlueSpark.h"
#include "Game/BlueDebris.h"
#include "Game/WhiteSmog.h"
#include "Game/ColorfulDebris.h"
#include "Game/ExplosionFlare.h"
#include "Game/Explosion.h"
#include "Game/MissileHit.h"

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
	controllers[GameParticle::ExplosionFlare] = new Effect::Game::ExplosionFlareController();
	controllers[GameParticle::MeteorExplosion] = new Effect::Game::ExplosionController();
	controllers[GameParticle::MissileHit] = new Effect::Game::MissileHitController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
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
隕石落下イベントのエフェクトセット処理
***************************************/
void GameParticleManager::SetMeteorExplosionEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	const D3DXVECTOR3 OffsetPosition = Vector3::Up * 10.0f;

	controllers[GameParticle::ExplosionFlare]->SetEmitter(position + OffsetPosition, callback);
	controllers[GameParticle::MeteorExplosion]->SetEmitter(position + OffsetPosition);
}

/**************************************
ミサイル命中イベントのエフェクトセット処理
***************************************/
void GameParticleManager::SetMissileHitEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[GameParticle::ExplosionFlare]->SetEmitter(position, callback);
	controllers[GameParticle::MissileHit]->SetEmitter(position);
}
