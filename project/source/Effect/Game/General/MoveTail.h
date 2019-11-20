//=============================================================================
//
// 移動の残像エフェクトクラス [MoveTail.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _MoveTail_H_
#define _MoveTail_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"

/**************************************
前方宣言
***************************************/

namespace Effect::Game
{
	/**************************************
	MoveTailControllerクラス
	***************************************/
	class MoveTailController : public BaseParticleController
	{
	public:
		MoveTailController();
		void SetEmitterPos(D3DXVECTOR3 Pos);
		bool Draw() override;
	};

	/**************************************
	MoveTailクラス
	***************************************/
	class MoveTail : public Particle3D
	{
	public:
		MoveTail();

		void Init() override;
		void Update() override;
	private:
		static const int Life;
	};
}


#endif