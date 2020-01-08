//=====================================
//
//AnimationParticle2D.h
//機能:アニメーションパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ANIMATIONPARTICLE2D_H_
#define _ANIMATIONPARTICLE2D_H_

#include "../../../main.h"
#include "Particle2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class AnimationParticle2D : public Particle2D
{
	using Particle2D::Particle2D;
public:
	AnimationParticle2D(float fivX, float divY);
	AnimationParticle2D(float divX, float divY, int life);
	AnimationParticle2D(float divX, float divY, int lifeMin, int lifeMax);
	AnimationParticle2D(const AnimationParticle2D& rhs);

	void SetAnimParameter(float texDixX, float texDivY);
	void SetAnimParameter(const D3DXVECTOR2& texDiv);

protected:
	void Animation(float t);

	int animIndexMax;
	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;
};
#endif