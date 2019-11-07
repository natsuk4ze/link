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
		AngryFace,		//怒り顔
		TownExplosion,	//隕石爆発
		MeteorExplosion,//ミサイル命中
		Darkness,		//闇の粒子(AIレベル減少イベント)
		Bubble,			//水の泡
		MoveTail,		//移動の軌跡
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
	//町消滅のエフェクトセット処理
	void SetTownExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//隕石爆発のエフェクトセット処理
	void SetMeteorExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//怒り顔のエフェクトセット処理
	void SetAngryFaceEffect(std::function<void(void)> callback = nullptr);
	//闇の粒子のエフェクトセット処理
	void SetDarknessEffect(const D3DXVECTOR3 & position,std::function<void(void)> callback = nullptr);
	//アトランティスのエフェクトセット処理
	void SetArtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);
	//移動の軌跡のエフェクトセット処理
	BaseEmitter* SetMoveTailEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif