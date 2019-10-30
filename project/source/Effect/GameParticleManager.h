//=====================================
//
// GameParticleManager.h
// 機能:ゲームシーンのパーティクルマネージャ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEPARTICLEMANAGER_H_
#define _GAMEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
ゲームシーンのパーティクル通し番号
***************************************/
namespace GameParticle
{
	enum ID
	{
		BlueSpark,		//ブルースパーク
		BlueDebris,		//ブルースパークの破片
		WhiteSmog,		//白い煙
		ColorfulDebis,	//カラフルデブリ
		ExplosionFlare,	//火の粉
		MeteorExplosion,//隕石爆発
		MissileHit,		//ミサイル命中
		Max
	};
}

/**************************************
クラス定義
***************************************/
class GameParticleManager : public SceneParticleManager, public BaseSingleton<GameParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	//初期化処理
	void Init() override;

	//シンギュラリティイベントのエフェクトセット処理
	void SetSingularityEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//隕石落下イベントのエフェクトセット処理
	void SetMeteorExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//ミサイル命中イベントのエフェクトセット処理
	void SetMissileHitEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif