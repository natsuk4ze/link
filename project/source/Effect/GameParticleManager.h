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
		WhiteSmog,		//白い煙
		ColorfulDebis,	//カラフルデブリ
		ExplosionFlare,	//火の粉
		AngryFace,		//怒り顔
		TownExplosion,	//隕石爆発
		MeteorExplosion,//ミサイル命中
		Darkness,		//闇の粒子(AIレベル減少イベント)
		LinkLevelUp,	//リンクレベルアップ時エフェクト
		Cloud,			//雲
		EventInfo,		//イベントます
		BlueAura,		//青オーラ
		PunchEffect,	//パンチエフェクト
		GaudeDebris,	//ゲージ破片
		EventHappen,	//イベント発生エフェクト
		RouteTrace,		//ルートエフェクト
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

	//描画処理
	void Draw() override;

	//町消滅のエフェクトセット処理
	void SetTownExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//隕石爆発のエフェクトセット処理
	void SetMeteorExplosionEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);
	//怒り顔のエフェクトセット処理
	void SetAngryFaceEffect(std::function<void(void)> callback = nullptr);
	//闇の粒子のエフェクトセット処理
	void SetDarknessEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);

	//オーラエフェクトセット処理
	BaseEmitter* SetAuraEffect(const D3DXVECTOR3& position, const D3DXVECTOR3& direction, std::function<void()> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif