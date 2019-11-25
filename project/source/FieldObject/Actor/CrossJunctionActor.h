//=====================================
//
// クロスジャンクションアクター[CrossJunctionActor.h]
// 機能：十字路3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CROSSJUNCTIONACTOR_H_
#define _CROSSJUNCTIONACTOR_H_

#include "PlaceActor.h"

//**************************************
// マクロ定義
//**************************************
class BaseEmitter;

//**************************************
// クラス定義
//**************************************
class CrossJunctionActor :
	public PlaceActor
{
private:

public:
	CrossJunctionActor();
	~CrossJunctionActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	void Uninit() override;
	void Draw() override;
	void Rotate(float y) override;

private:
	std::vector<BaseEmitter*> emitterContainer;
	bool onWater;
};

#endif
