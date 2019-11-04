//=====================================
//
// メタモルパスアクター[MetamorPassActor.h]
// 機能：フィールド上を行き来するアクター（国レベルで使用。モデルが動的に切り替わる）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _METAMORPASSACTOR_H_
#define _METAMORPASSACTOR_H_

#include "PassengerActor.h"

//**************************************
// クラス定義
//**************************************
class MetamorPassActor :
	public PassengerActor
{

public:
	MetamorPassActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~MetamorPassActor();

};

#endif
