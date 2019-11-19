//=====================================
//
//WorldParticleManager.cpp
//機能:世界レベルのパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WorldParticleManager.h"
#include "../../Framework/Particle/BaseParticleController.h"
#include "../../Framework/PostEffect/CrossFilterController.h"

#include "Game/World/Bubble.h"
#include "Game\World\WaterSmog.h"

/**************************************
staticメンバ
***************************************/
const float WorldParticleManager::BloomPower[3] = { 1.0f, 1.0f, 1.0f };
const float WorldParticleManager::BloomThrethold[3] = { 0.46f, 0.35f, 0.18f };

/**************************************
初期化処理
***************************************/
void WorldParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(WorldParticle::Max, nullptr);
	controllers[WorldParticle::Bubble] = new Effect::Game::BubbleController();

	crossFilter->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	crossFilter->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);
}

/**************************************
アトランティスエフェクトセット処理
***************************************/
void WorldParticleManager::SetAtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback)
{
	controllers[WorldParticle::Bubble]->SetEmitter(position, callback);
}
