//=====================================
//
//Blackhole.h
//機能:ブラックホールパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BLACKHOLE_H_
#define _BLACKHOLE_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/BaseEmitter.h"

namespace Effect::Game
{
	/**************************************
	BlackholeController
	***************************************/
	class BlackholeController : public BaseParticleController
	{
	public:
		BlackholeController();
	};

	/**************************************
	Blackhole
	***************************************/
	class Blackhole : public Particle3D
	{
	public:
		Blackhole();

		void Init();
		void Update();

		static const float InitOffset;
		static const float RangeHeight;

	private:
		D3DXVECTOR3 position;
		float height;
		float initAngle;
		float initScale;
	};

	/**************************************
	BlackholeEmitter
	***************************************/
	class BlackholeEmitter : public BaseEmitter
	{
	public:
		BlackholeEmitter();

		bool IsActive() const override;
	};
}


#endif