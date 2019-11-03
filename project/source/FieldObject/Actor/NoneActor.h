//=====================================
//
// ノンアクター[NoneActor.h]
// 機能：何もアクターがない状態を表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _NONEACTOR_H_
#define _NONEACTOR_H_

#include "PlaceActor.h"

//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class NoneActor :
	public PlaceActor
{
private:
public:
	NoneActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~NoneActor();
};

#endif
