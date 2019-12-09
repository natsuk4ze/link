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
	TJunctionActor();
	~TJunctionActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	void Uninit() override;
	void Draw() override;
	void Rotate(float y) override;

	void OnSea(bool statea) override;

private:
	std::vector<BaseEmitter*> emitterContainer;
	bool onWater;
};

#endif
