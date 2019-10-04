//=====================================
//
// マウンテンアクター[MountainActor.h]
// 機能：山（渦潮、ブラックホール）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _MOUNTAINACTOR_H_
#define _MOUNTAINACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class MountainActor :
	public PlaceActor
{
public:
	MountainActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~MountainActor();

	void Update()override;
};

#endif
