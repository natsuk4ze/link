//=====================================
//
// セレクトロゴ[SelectLogo.cpp]
// 機能：セレクトロゴ
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "SelectLogo.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
SelectLogo::SelectLogo()
{
	polygon = new BoardPolygon();
}

//=====================================
// デストラクタ
//=====================================
SelectLogo::~SelectLogo()
{
	SAFE_DELETE(polygon);
}

//=====================================
// 更新
//=====================================
void SelectLogo::Update()
{
}

//=====================================
// 描画
//=====================================
void SelectLogo::Draw()
{
	polygon->Draw(transform->GetMatrix());
}

//=====================================
// リソース読み込み
//=====================================
void SelectLogo::LoadResource(const char * tag)
{
	ResourceManager::Instance()->GetPolygon(tag, polygon);
}

//=====================================
// 座標セット
//=====================================
void SelectLogo::SetPosition(const D3DXVECTOR3 & pos)
{
	transform->SetPosition(pos);
}

//=====================================
// 分割数セット
//=====================================
void SelectLogo::SetTexDiv(const D3DXVECTOR2& div)
{
	polygon->SetTexDiv(div);
}

//=====================================
// テクスチャの変更
//=====================================
void SelectLogo::SetTextureIndex(int index)
{
	polygon->SetTextureIndex(index);
}
