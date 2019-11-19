//=====================================
//
//SpaceTear.h
//機能:時空断裂パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPACETEAR_H_
#define _SPACETEAR_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseEmitter.h"

namespace Effect::Game
{
	/**************************************
	SpaceTearControllerクラス
	***************************************/
	class SpaceTearController : public BaseParticleController
	{
	public:
		SpaceTearController();
	};

	/**************************************
	SpaceTearクラス
	***************************************/
	class SpaceTear : public Particle3D
	{
	public:
		SpaceTear();

		void Init() override;
		void Update() override;

	private:
		static const int MaxLife, MinLife;

		float angleRotate;
		float initScaleX;
		float initScaleY;
	};

	/**************************************
	SpaceTearEmitterクラス
	***************************************/
	class SpaceTearEmitter : public BaseEmitter
	{
	public:
		SpaceTearEmitter();

		bool IsActive() const override;
	};
}
#endif