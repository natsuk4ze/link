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

//**************************************
// クラス定義
//**************************************
class CrossJunctionActor :
	public PlaceActor
{
private:

public:
	CrossJunctionActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~CrossJunctionActor();
	void Update()override;
	//void Draw()override;
};

#endif
