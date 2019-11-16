//=====================================
//
// Tジャンクションアクター[TJunctionActor.h]
// 機能：T字路3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _TJUNCTIONACTOR_H_
#define _TJUNCTIONACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************
class BaseEmitter;

//**************************************
// クラス定義
//**************************************
class TJunctionActor :
	public PlaceActor
{
public:
	TJunctionActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~TJunctionActor();

	void Rotate(float y) override;

private:
	std::vector<BaseEmitter*> emitterContainer;
};

#endif
