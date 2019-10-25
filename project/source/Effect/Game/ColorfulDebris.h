//=====================================
//
// ColorfulDebris.h
// 機能:カラフルデブリパーティクル
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _COLORFULDEBRIS_H_
#define _COLORFULDEBRIS_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	ColorfulDebrisController
	***************************************/
	class ColorfulDebrisController : public BaseParticleController
	{
	public:
		ColorfulDebrisController();
	};

	/**************************************
	ColorfulDebris
	***************************************/
	class ColorfulDebris : public Particle3D
	{
	public:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;
		static const float MinScale, MaxScale;
		static const int TexDiv;

		ColorfulDebris();

		void Init();
		void Update();

	private:
		float initSpeed;
		float initScale;
		D3DXVECTOR3 directionMove;
	};
}
#endif