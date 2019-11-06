//=============================================================================
//
// 移動の残像エフェクトクラス [Tail.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _Tail_H_
#define _Tail_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

/**************************************
前方宣言
***************************************/

namespace Effect::Game
{
	/**************************************
	TailControllerクラス
	***************************************/
	class TailController : public BaseParticleController
	{
	public:
		TailController();
	};

	/**************************************
	Tailクラス
	***************************************/
	class Tail : public Particle3D
	{
	public:
		Tail();

		void Init() override;
		void Update() override;

	private:
		static const int Life;
	};
}


#endif