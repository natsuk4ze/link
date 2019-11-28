//=====================================
//
//SpaceParticleManager.cpp
//機能:宇宙レベルのパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpaceParticleManager.h"
#include "../../Framework/Particle/BaseParticleController.h"
#include "../../Framework/PostEffect/CrossFilterController.h"

#include "Game/Space/SpaceTear.h"
#include "Game/Space/StarRoad.h"
#include "Game/Space/Blackhole.h"
#include "Game/Space/MoveTail.h"
#include "Game/Space/StarDust.h"

/**************************************
staticメンバ
***************************************/
const float SpaceParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float SpaceParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
初期化処理
***************************************/
void SpaceParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(SpaceParticle::Max, nullptr);
	controllers[SpaceParticle::SpaceTear] = new Effect::Game::SpaceTearController();
	controllers[SpaceParticle::StarRoad] = new Effect::Game::StarRoadController();
	controllers[SpaceParticle::Blackhole] = new Effect::Game::BlackholeController();
	controllers[SpaceParticle::MoveTail] = new Effect::Game::MoveTailController();
	controllers[SpaceParticle::StarDust] = new Effect::Game::StarDustController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
惑星登場のエフェクトセット処理
***************************************/
void SpaceParticleManager::SetPlanetFallEffect(const D3DXVECTOR3 & position, BaseEmitter ** MoveTail, BaseEmitter ** StarDust)
{
	*MoveTail = controllers[SpaceParticle::MoveTail]->SetEmitter(position, nullptr);
	*StarDust = controllers[SpaceParticle::StarDust]->SetEmitter(position, nullptr);
}
