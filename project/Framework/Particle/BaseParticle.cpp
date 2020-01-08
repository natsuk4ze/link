//=====================================
//
//ベースパーティクル処理[BaseParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseParticle.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle() :
	uv(ParticleUV()),
	lifeFrame(1), maxLife(1), minLife(1)
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(int life) :
	uv(ParticleUV()),
	lifeFrame(life), minLife(life), maxLife(1)
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(int lifeMin, int lifeMax) :
	uv(ParticleUV()),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax)),
	minLife(lifeMin), maxLife(lifeMax)
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(float u, float v, int lifeMin, int lifeMax) :
	uv(ParticleUV(u, v)),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax)),
	minLife(lifeMin), maxLife(lifeMax)
{
}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(const BaseParticle & rhs) :
	uv(rhs.uv),
	lifeFrame(Math::RandomRange(rhs.maxLife, rhs.minLife)),
	minLife(rhs.minLife), maxLife(rhs.maxLife)
{
}

/**************************************
デストラクタ
***************************************/
BaseParticle::~BaseParticle()
{
}

/**************************************
UV座標取得
***************************************/
ParticleUV BaseParticle::GetUV() const
{
	return uv;
}

/**************************************
アクティブ判定
***************************************/
bool BaseParticle::_IsActive() const
{
	return cntFrame <= lifeFrame;
}
