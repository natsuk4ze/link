//=============================================================================
//
// 隕石爆発エフェクトクラス [MeteorExplosion.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _MeteorExplosion_H_
#define _MeteorExplosion_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	MeteorExplosionControllerクラス
	***************************************/
	class MeteorExplosionController : public BaseParticleController
	{
	public:
		MeteorExplosionController();
	};

	/**************************************
	MeteorExplosionクラス
	***************************************/
	class MeteorExplosion : public AnimationParticle3D
	{
	public:
		MeteorExplosion();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}
#endif