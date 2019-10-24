//=============================================================================
//
// 爆発エフェクトクラス [Explosion.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _Explosion_H_
#define _Explosion_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/AnimationParticle.h"

namespace Effect::Game
{
	/**************************************
	ExplosionControllerクラス
	***************************************/
	class ExplosionController : public BaseParticleController
	{
	public:
		ExplosionController();
	};

	/**************************************
	Explosionクラス
	***************************************/
	class Explosion : public AnimationParticle
	{
	public:
		Explosion();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
		static const float Speed;

		D3DXVECTOR3 directionMove;
		float speedMove;
	};
}
#endif