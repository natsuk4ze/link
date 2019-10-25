//=====================================
//
//Particle3D.h
//機能:パーティクル3D
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

#include "../../main.h"
#include "BaseParticle.h"
#include "../Renderer3D/BillboardObject.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class Particle3D : public BaseParticle, public BillboardObject
{
public:
	Particle3D();
	Particle3D(int life);
	Particle3D(int minLife, int maxLife);
	Particle3D(float u, float v, int minLife, int maxLife);
	virtual ~Particle3D();

	virtual bool IsActive() const;

	virtual void SetTransform(const Transform& transform);

	virtual void SetActive(bool state);

	virtual D3DXMATRIX GetWorldMtx();
};

#endif