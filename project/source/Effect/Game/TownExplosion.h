//=============================================================================
//
// 町消滅エフェクトクラス [TownExplosion.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TownExplosion_H_
#define _TownExplosion_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	TownExplosionControllerクラス
	***************************************/
	class TownExplosionController : public BaseParticleController
	{
	public:
		TownExplosionController();
	};

	/**************************************
	TownExplosionクラス
	***************************************/
	class TownExplosion : public AnimationParticle3D
	{
	public:
		TownExplosion();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}
#endif