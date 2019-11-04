//=====================================
//
// メタモルパスアクター[MetamorPassActor.cpp]
// 機能：フィールド上を行き来するアクター（国レベルで使用。モデルが動的に切り替わる）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "MetamorPassActor.h"

//=====================================
// コンストラクタ
//=====================================
MetamorPassActor::MetamorPassActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel) :
	PassengerActor(pos, currentLevel)
{

}

//=====================================
// デストラクタ
//=====================================
MetamorPassActor::~MetamorPassActor()
{
}

//=====================================
// ワールド座標からPlaceModelの座標に変換する
//=====================================
Field::FieldPosition MetamorPassActor::ConvertToFieldPosition()
{
	D3DXVECTOR3 pos = transform->GetPosition();
	Field::FieldPosition ret;

	ret.x = (int)pos.x / 10;
	ret.z = abs((int)pos.z / 10);

	return ret;
}
