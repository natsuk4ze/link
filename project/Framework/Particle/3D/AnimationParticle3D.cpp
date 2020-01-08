//=====================================
//
//アニメーションパーティクル処理[AnimationParticle3D.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AnimationParticle3D.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
AnimationParticle3D::AnimationParticle3D(float divX, float divY) :
	Particle3D()
{
	SetAnimParameter(divX, divY);
}

/**************************************
コンストラクタ
***************************************/
AnimationParticle3D::AnimationParticle3D(float divX, float divY, int life) :
	Particle3D(life)
{
	SetAnimParameter(divX, divY);
};

/**************************************
コンストラクタ
***************************************/
AnimationParticle3D::AnimationParticle3D(float divX, float divY, int lifeMin, int lifeMax) :
	Particle3D(lifeMin, lifeMax)
{
	SetAnimParameter(divX, divY);
}

/**************************************
コンストラクタ
***************************************/
AnimationParticle3D::AnimationParticle3D(const AnimationParticle3D & rhs) :
	Particle3D(rhs)
{
	SetAnimParameter(rhs.texDiv.x, rhs.texDiv.y);
}

/**************************************
アニメーション処理
***************************************/
void AnimationParticle3D::Animation(float t)
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
void AnimationParticle3D::SetAnimParameter(float divX, float divY)
{
	texDiv = D3DXVECTOR2(divX, divY);
	texSize.x = 1.0f / divX;
	texSize.y = 1.0f / divY;

	animIndexMax = (int)(divX * divY) - 1;
}

/**************************************
アニメーションパラメータセット処理
***************************************/
void AnimationParticle3D::SetAnimParameter(const D3DXVECTOR2& texDiv)
{
	this->texDiv = texDiv;
	texSize.x = 1.0f / texDiv.x;
	texSize.y = 1.0f / texDiv.y;

	animIndexMax = (int)(texDiv.x * texDiv.y) - 1;
}