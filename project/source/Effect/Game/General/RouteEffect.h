//=====================================
//
//RouteEffect.h
//機能:ルートエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ROUTEEFFECT_H_
#define _ROUTEEFFECT_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	RouteEffectController
	***************************************/
	class RouteEffectController : public BaseParticleController
	{
	public:
		RouteEffectController();
	};

	/**************************************
	RouteEffect
	***************************************/
	class RouteEffect : public Particle3D
	{
	public:
		RouteEffect();

		void Init();
		void Update();

		static const float InitSpeed;

	private:
		D3DXVECTOR3 moveDir;
	};
}

#endif