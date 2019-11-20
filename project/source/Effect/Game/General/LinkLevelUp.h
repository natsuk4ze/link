//=====================================
//
//LinkLevelUp.h
//機能:リンクレベルアップ時の2Dパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _LINKLEVELUP_H_
#define _LINKLEVELUP_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	LinkLevelUpController
	***************************************/
	class LinkLevelUpController : public BaseParticleController
	{
	public:
		LinkLevelUpController();
	};

	/**************************************
	LinkLevelUpクラス
	***************************************/
	class LinkLevelUp : public Particle2D
	{
	public:
		LinkLevelUp();
		~LinkLevelUp();

		void Init();
		void Update();

	private:
		D3DXVECTOR3 directionMove;
		float speed;
		float initScale;
	};
}
#endif