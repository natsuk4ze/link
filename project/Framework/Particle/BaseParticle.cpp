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
	BillboardObject(false),
	uv(ParticleUV())
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(int life) :
	BillboardObject(false),
	uv(ParticleUV()),
	lifeFrame(life)
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(int lifeMin, int lifeMax) :
	BillboardObject(false),
	uv(ParticleUV()),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax))
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(float u, float v, int lifeMin, int lifeMax) :
	BillboardObject(false),
	uv(ParticleUV(u, v)),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax))
{
}

/**************************************
デストラクタ
***************************************/
BaseParticle::~BaseParticle()
{
}

/**************************************
アクティブ判定
***************************************/
bool BaseParticle::IsActive() const
{
	if (!active)
		return false;

	return cntFrame <= lifeFrame;
}

/**************************************
ワールド行列行列取得処理
***************************************/
D3DXMATRIX BaseParticle::GetWorldMtx()
{
	return transform->GetMatrix();
}
