//=====================================
//
//WorldParticleManager.h
//機能:世界レベルのパーティクルマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WRORLDPARTICLEMANAGER_H_
#define _WRORLDPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
ワールドレベルのパーティクル通し番号
***************************************/
namespace WorldParticle
{
	enum ID
	{
		Bubble,				//水の泡
		WhirlPoolBubble,	//渦潮の泡
		Max
	};
}

/**************************************
クラス定義
***************************************/
class WorldParticleManager : public SceneParticleManager, public BaseSingleton<WorldParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	void Init() override;

	//アトランティスのエフェクトセット処理
	void SetAtlantisEffect(const D3DXVECTOR3 & position, std::function<void(void)> callback = nullptr);

private:
	static const float BloomPower[3];
	static const float BloomThrethold[3];
};

#endif