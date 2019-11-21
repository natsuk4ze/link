//=====================================
//
// ブリッジアクター[BridgeActor.cpp]
// 機能：橋（ワープホール）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _BRIDGEACTOR_H_
#define _BRIDGEACTOR_H_

#include "PlaceActor.h"
//**************************************
// マクロ定義
//**************************************
namespace Field::Actor
{
	class RiverEffect;
}

//**************************************
// クラス定義
//**************************************
class BridgeActor :
	public PlaceActor
{
public:
	BridgeActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~BridgeActor();

	virtual void Update() override;
	virtual void Draw() override;

private:
	Field::Actor::RiverEffect *effect;
	D3DXVECTOR2 uv;
};

#endif
