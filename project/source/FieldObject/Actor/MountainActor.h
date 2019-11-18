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
namespace Field::Actor
{
	class WhirlPoolEffect;
}

//**************************************
// クラス定義
//**************************************
class MountainActor :
	public PlaceActor
{
public:
	MountainActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel, bool onWater);
	~MountainActor();

	void Update() override;
	void Draw() override;

private:
	Field::Actor::WhirlPoolEffect *effect;
	float speedWhirl;
	float cntWhirl;
};

#endif
