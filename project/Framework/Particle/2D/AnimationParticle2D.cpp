//=====================================
//
//AnimationParticle2D.cpp
//機能:アニメーションパーティクル2D
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AnimationParticle2D.h"

/**************************************
コンストラクタ
***************************************/
AnimationParticle2D::AnimationParticle2D(float divX, float divY) :
	Particle2D()
{
	SetAnimParameter(divX, divY);
}

/**************************************
コンストラクタ
***************************************/
AnimationParticle2D::AnimationParticle2D(float divX, float divY, int life) :
	Particle2D(life)
{
	SetAnimParameter(divX, divY);
};

/**************************************
コンストラクタ
***************************************/
AnimationParticle2D::AnimationParticle2D(float divX, float divY, int lifeMin, int lifeMax) :
	Particle2D(lifeMin, lifeMax)
{
	SetAnimParameter(divX, divY);
}

/**************************************
アニメーション処理
***************************************/
void AnimationParticle2D::Animation(float t)
{
	int animIndex = (int)(t * animIndexMax);

	int x = animIndex % (int)texDiv.x;
	int y = animIndex / (int)texDiv.x;

	uv.u = x * texSize.x;
	uv.v = y * texSize.y;
}

/**************************************
アニメーションパラメータセット処理
***************************************/
void AnimationParticle2D::SetAnimParameter(float divX, float divY)
{
	texDiv = D3DXVECTOR2(divX, divY);
	texSize.x = 1.0f / divX;
	texSize.y = 1.0f / divY;

	animIndexMax = (int)(divX * divY) - 1;
}

/**************************************
アニメーションパラメータセット処理
***************************************/
void AnimationParticle2D::SetAnimParameter(const D3DXVECTOR2& texDiv)
{
	this->texDiv = texDiv;
	texSize.x = 1.0f / texDiv.x;
	texSize.y = 1.0f / texDiv.y;

	animIndexMax = (int)(texDiv.x * texDiv.y) - 1;
}