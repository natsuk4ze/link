//=====================================
//
//WhirlPool.h
//機能:渦潮レンダラー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WHIRLPOOL_H_
#define _WHIRLPOOL_H_

#include "../../main.h"
#include "../../Framework/Effect/RendererEffect.h"

namespace Field::Actor
{
	/**************************************
	クラス定義
	***************************************/
	class WhirlPoolEffect : public RendererEffect
	{
	public:
		WhirlPoolEffect();
		~WhirlPoolEffect();

		void SetWorld(const Transform& transform);

		void SetTime(float t);

	private:
		D3DXHANDLE hTime;

	};
}


#endif