//=====================================
//
// リバーアクター[RiverActor.h]
// 機能：川（時空断裂）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _RIVERACTOR_H_
#define _RIVERACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class RiverActor :
	public PlaceActor
{
public:
	RiverActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~RiverActor();
};

#endif
