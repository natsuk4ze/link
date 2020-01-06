//=====================================
//
//Particle2D.cpp
//機能:2Dパーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Particle2D.h"

/**************************************
コンストラクタ
***************************************/
Particle2D::Particle2D() :
	BaseParticle(),
	GameObject(false)
{
}

/**************************************
コンストラクタ
***************************************/
Particle2D::Particle2D(int life) :
	BaseParticle(life),
	GameObject(false)
{
}

/**************************************
コンストラクタ
***************************************/
Particle2D::Particle2D(int minLife, int maxLife) :
	BaseParticle(minLife, maxLife),
	GameObject(false)
{
}

/**************************************
コンストラクタ
***************************************/
Particle2D::Particle2D(float u, float v, int minLife, int maxLife) :
	BaseParticle(u, v, minLife, maxLife),
	GameObject(false)
{
}

/**************************************
コンストラクタ
***************************************/
Particle2D::Particle2D(const Particle2D & rhs) :
	BaseParticle(rhs),
	GameObject(false)
{
}

/**************************************
デストラクタ
***************************************/
Particle2D::~Particle2D()
{
}

/**************************************
コンストラクタ
***************************************/
bool Particle2D::IsActive() const
{
	if (!active)
		return false;

	return _IsActive();
}

/**************************************
トランスフォーム設定処理
***************************************/
void Particle2D::SetTransform(const Transform & transform)
{
	GameObject::SetTransform(transform);
}

/**************************************
アクティブセット処理
***************************************/
void Particle2D::SetActive(bool state)
{
	GameObject::SetActive(state);
}

/**************************************
ワールド変換行列取得処理
***************************************/
D3DXMATRIX Particle2D::GetWorldMtx()
{
	return transform->GetMatrix();
}
