//=====================================
//
// ストレートロードアクター[StraightRoadActor.cpp]
// 機能：まっすぐな道用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _STRAIGHTROADACTOR_H_
#define _STRAIGHTROADACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class StraightRoadActor :
	public PlaceActor
{
public:
	StraightRoadActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~StraightRoadActor();

	void Update()override;
};

#endif
