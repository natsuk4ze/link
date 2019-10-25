//=============================================================================
//
// ミサイル命中クラス [MissileHit.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _MissileHit_H_
#define _MissileHit_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/AnimationParticle.h"

namespace Effect::Game
{
	/**************************************
	MissileHitControllerクラス
	***************************************/
	class MissileHitController : public BaseParticleController
	{
	public:
		MissileHitController();
	};

	/**************************************
	MissileHitクラス
	***************************************/
	class MissileHit : public AnimationParticle
	{
	public:
		MissileHit();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
		static const float Speed;

		float speedMove;
	};
}
#endif