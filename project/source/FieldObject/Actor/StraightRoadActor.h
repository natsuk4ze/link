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
class BaseEmitter;

//**************************************
// クラス定義
//**************************************
class StraightRoadActor :
	public PlaceActor
{
public:
	StraightRoadActor();
	~StraightRoadActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWataer);
	void Uninit() override;
	void Draw() override;

	void Rotate(float y) override;

	void OnSea(bool state) override;

private:
	BaseEmitter * emitter;
	bool onWater;
};

#endif
