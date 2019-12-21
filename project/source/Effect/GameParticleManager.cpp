//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Particle/BaseParticleController.h"

#include "Game/General/WhiteSmog.h"
#include "Game/General/ColorfulDebris.h"
#include "Game/General/ExplosionFlare.h"
#include "Game/General/TownExplosion.h"
#include "Game/General/MeteorExplosion.h"
#include "Game/General/AngryFace.h"
#include "Game/General/Darkness.h"
#include "Game/General/LinkLevelUp.h"
#include "Game/General/Cloud.h"
#include "Game/General/EventInfo.h"
#include "Game\General\AuraEffect.h"
#include "Game\General\PunchEffect.h"
#include "Game\General\GaugeDebris.h"
#include "Game/General/EventHappen.h"
#include "Game\General\RouteEffect.h"
#include "Game/General/Linkup.h"

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
	controllers[GameParticle::WhiteSmog] = new Effect::Game::WhiteSmogController();
	controllers[GameParticle::ColorfulDebis] = new Effect::Game::ColorfulDebrisController();
	controllers[GameParticle::ExplosionFlare] = new Effect::Game::ExplosionFlareController();
	controllers[GameParticle::AngryFace] = new Effect::Game::AngryFaceController();
	controllers[GameParticle::TownExplosion] = new Effect::Game::TownExplosionController();
	controllers[GameParticle::MeteorExplosion] = new Effect::Game::MeteorExplosionController();
	controllers[GameParticle::Darkness] = new Effect::Game::DarknessController();
	controllers[GameParticle::LinkLevelUp] = new Effect::Game::LinkLevelUpController();
	controllers[GameParticle::Cloud] = new Effect::Game::CloudController();
	controllers[GameParticle::EventInfo] = new Effect::Game::EventInfoEffectController();
	controllers[GameParticle::BlueAura] = new Effect::Game::AuraEffectController();
	controllers[GameParticle::PunchEffect] = new Effect::Game::PunchEffectController();
	controllers[GameParticle::GaudeDebris] = new Effect::Game::GaugeDebrisController();
	controllers[GameParticle::EventHappen] = new Effect::Game::EventHappenController();
	controllers[GameParticle::RouteTrace] = new Effect::Game::RouteEffectController();
	controllers[GameParticle::LinkUp] = new Effect::Game::LinkLevelUpController();

 	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
描画処理
***************************************/
void GameParticleManager::Draw()
{
	SceneParticleManager::Draw();

	//Debug::Begin("GameParticle");
	//Debug::Text("Cloud : %d", controllers[GameParticle::Cloud]->GetParticleCount());
	//Debug::End();
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
オーラエフェクトセット処理
***************************************/
BaseEmitter* GameParticleManager::SetAuraEffect(const D3DXVECTOR3 & position, const D3DXVECTOR3 & direction, std::function<void()> callback)
{
	Effect::Game::AuraEffectController* controller = dynamic_cast<Effect::Game::AuraEffectController*>(controllers[GameParticle::BlueAura]);
	return controller->SetEmitter(position, direction, callback);
}
