//=====================================
//
//RiverEffect.h
//機能:RiverActor描画シェーダ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RIVEREFFECT_H_
#define _RIVEREFFECT_H_

#include "../../main.h"
#include "../../Framework/Effect/RendererEffect.h"

namespace Field::Actor
{
	/**************************************
	クラス定義
	***************************************/
	class RiverEffect : public RendererEffect
	{
	public:
		RiverEffect();
		~RiverEffect();

		void SetWorld(const Transform& transform);
		void SetUV(const D3DXVECTOR2& uv);

	private:
		D3DXHANDLE hTexUV;
	};
}

#endif