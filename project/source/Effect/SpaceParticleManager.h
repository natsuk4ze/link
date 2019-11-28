//=====================================
//
//SpaceParticleManager.h
//機能:宇宙レベルのパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPACEPARTICLEMANAGER_H_
#define _SPACEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
前方宣言
***************************************/
namespace SpaceParticle
{
	enum ID
	{
		SpaceTear,		//時空断裂のスパーク,
		StarRoad,		//銀河道
		Blackhole,		//ブラックホール
		MoveTail,		//移動の軌跡
		StarDust,		//惑星落下のスターダスト
		Max
	};
}

/**************************************
クラス定義
***************************************/
class SpaceParticleManager : public SceneParticleManager, public BaseSingleton<SpaceParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	void Init() override;

	//惑星登場のエフェクトセット処理
	void SetPlanetFallEffect(const D3DXVECTOR3 & position, BaseEmitter** MoveTail, BaseEmitter** StarDust);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};
#endif