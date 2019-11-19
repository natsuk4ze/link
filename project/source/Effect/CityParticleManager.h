//=====================================
//
//CityParticleManager.h
//機能:街レベルのパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CITYPARTICLEMANAGER_H_
#define _CITYPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
街レベルのパーティクル通し番号
***************************************/
namespace CityParticle
{
	enum ID
	{
		BlueDebris,		//ブルースパーク
		BlueSpark,		//ブルースパークの破片
		Max
	};
}

/**************************************
クラス定義
***************************************/
class CityParticleManager : public SceneParticleManager, public BaseSingleton<CityParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	//初期化処理
	void Init() override;

	//シンギュラリティイベントのエフェクトセット処理
	void SetSingularityEffect(const D3DXVECTOR3& position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif