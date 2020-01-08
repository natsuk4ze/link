//=====================================
//
//WhirlPoolBubble.h
//‹@”\:‰Q’ª‚Ì–A
//Author:GP12B332 21 —§‰Ô—Y‘¾
//
//=====================================
#ifndef _WHIRLPOOLBUBBLE_H_
#define _WHIRLPOOLBUBBLE_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	WhirlPoolBubbleController
	***************************************/
	class WhirlPoolController : public BaseParticleController
	{
	public:
		WhirlPoolController();
	};

	/**************************************
	WhirlPoolBubble
	***************************************/
	class WhirlPoolBubble : public Particle3D
	{
	public:
		WhirlPoolBubble();

		void Init() override;
		void Update() override;

	private:
		static const float LengthPopup;
		static const float LengthOffset;

		D3DXVECTOR3 position;
		float initOffset;
	};

	/**************************************
	WhirlPoolBubbleEmitter
	***************************************/
	class WhirlPoolBubbleEmitter : public BaseEmitter
	{
	public:
		WhirlPoolBubbleEmitter();
	};
}


#endif