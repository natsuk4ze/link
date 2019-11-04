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
// 更新
//=====================================
void MetamorPassActor::Update()
{

}