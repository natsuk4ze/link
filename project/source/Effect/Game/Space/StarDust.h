//=============================================================================
//
// スターダストエフェクトクラス [StarDust.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _StarDust_H_
#define _StarDust_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	StarDustController
	***************************************/
	class StarDustController : public BaseParticleController
	{
	public:
		StarDustController();
		bool Draw(void) override;
		void SetEmitterPos(D3DXVECTOR3 Pos);
	};

	/**************************************
	StarDust
	***************************************/
	class StarDust : public Particle3D
	{
	public:
		static const int MinLife, MaxLife;
		static const float MinScale, MaxScale;
		static const int TexDiv;

		StarDust();
		void Init();
		void Update();

	private:
		float initScale;
		D3DXVECTOR3 directionMove;
	};
}
#endif