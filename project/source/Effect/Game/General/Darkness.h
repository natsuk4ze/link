//=============================================================================
//
// AIレベル減少エフェクトクラス [Darkness.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _Darkness_H_
#define _Darkness_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/AnimationParticle3D.h"

namespace Effect::Game
{
	/**************************************
	DarknessControllerクラス
	***************************************/
	class DarknessController : public BaseParticleController
	{
	public:
		DarknessController();
	};

	/**************************************
	Darknessクラス
	***************************************/
	class Darkness : public Particle3D
	{
	public:

		Darkness();

		void Init() override;
		void Update() override;

	private:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;
		static const int TexDiv;
		const float Speed;
	};
}
#endif