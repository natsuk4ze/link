//=====================================
//
// TestParticleManager.h
// 機能:ゲームシーンのパーティクルマネージャ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TESTPARTICLEMANAGER_H_
#define _TESTPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
パーティクル通し番号
***************************************/
namespace TestParticle
{
	enum ID
	{
		BlueSpark,
		BlueDebris,
		WhiteSmog,
		ExplosionFlare,
		AngryFace,
		TownExplosion,
		MeteorExplosion,
		MeteorFire,
		Darkness,
		Max
	};
}

/**************************************
クラス定義
***************************************/
class TestParticleManager : public SceneParticleManager, public BaseSingleton<TestParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	void Init() override;
	void Update() override;
	void Draw() override;
};

#endif