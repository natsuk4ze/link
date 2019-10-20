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

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameParticleManager : public SceneParticleManager
{
public:
	enum ParticleID
	{
		BlueSpark,
		Max
	};

	void Init() override;
};

#endif