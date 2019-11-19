//=============================================================================
//
// 隕石周りの炎エフェクトクラス [MeteorFire.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _MeteorFire_H_
#define _MeteorFire_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	MeteorFireControllerクラス
	***************************************/
	class MeteorFireController : public BaseParticleController
	{
	public:
		MeteorFireController();
	};

	/**************************************
	MeteorFireクラス
	***************************************/
	class MeteorFire : public AnimationParticle3D
	{
	public:
		MeteorFire();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
		int AnimIndex;
	};
}
#endif