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
	current = Ship;
	fieldPos = Field::FieldPosition::ConvertToFieldPosition(transform->GetPosition());
	change = false;
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
	if (!IsActive())
		return;

	// メッシュ切り替え確認
	CheckState();
}

//=====================================
// ステートの確認
//=====================================
void MetamorPassActor::CheckState()
{
	if (change)
	{
		if (current == Ship)
		{
			ChangeMesh("Train-World");
		}
		else if (current == Train)
		{
			ChangeMesh("Ship-Train");
		}
	}
}

//=====================================
// フィールド上の座標を返す
//=====================================
Field::FieldPosition MetamorPassActor::FieldPosition()
{
	return fieldPos = Field::FieldPosition::ConvertToFieldPosition(transform->GetPosition());
}

//=====================================
// メッシュ切り替えフラグのセット
//=====================================
void MetamorPassActor::SetChange(bool flag)
{
	change = flag;
}