//=====================================
//
//Particle2D.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "../../../main.h"
#include "../BaseParticle.h"
#include "../../Core/GameObject.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class Particle2D : public BaseParticle, public GameObject
{
public:
	Particle2D();
	Particle2D(int life);
	Particle2D(int minLife, int maxLife);
	Particle2D(float u, float v, int minLife, int maxLife);
	Particle2D(const Particle2D& rhs);
	virtual ~Particle2D();

	virtual bool IsActive() const;

	virtual void SetTransform(const Transform& transform);

	virtual void SetActive(bool state);

	virtual D3DXMATRIX GetWorldMtx();
};
#endif