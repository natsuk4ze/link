//=====================================
//
// カーブロードアクター[CurveRoadActor.h]
// 機能：カーブ用道3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CURVEROADACTOR_H_
#define _CURVEROADACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class CurveRoadActor :
	public PlaceActor
{
public:
	CurveRoadActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~CurveRoadActor();
};

#endif
