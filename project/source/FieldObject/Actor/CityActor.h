//=====================================
//
// シティアクター[CityActor.cpp]
// 機能：都市（国、星）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CITYACTOR_H_
#define _CITYACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class CityActor :
	public PlaceActor
{
public:
	CityActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~CityActor();
};

#endif
