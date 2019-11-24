//=====================================
//
// セレクトロゴ[SelectLogo.cpp]
// 機能：セレクトロゴ
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "SelectLogo.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// スタティックメンバ初期化
//**************************************
const float SelectLogo::Distance = 75.0f;
const int SelectLogo::MoveFrame = 15;
const D3DXVECTOR3 SelectLogo::InitLogoPos[] = {
	D3DXVECTOR3(0.0f, 0.0f, -Distance),
	D3DXVECTOR3(Distance * sinf(D3DXToRadian(-60)), 0.0f, Distance * cosf(D3DXToRadian(-60))),
	D3DXVECTOR3(Distance * sinf(D3DXToRadian(60)), 0.0f, Distance * cosf(D3DXToRadian(60)))
};

//=====================================
// コンストラクタ
//=====================================
SelectLogo::SelectLogo() :
	counter(0)
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

	// 移動
	if (moveRight || moveLeft)
	{
		if (counter < MoveFrame)
		{
			// 右回転
			if (moveRight)
			{
				angle -= 120.0f / (float)MoveFrame;
				if (angle <= -180.0f)
				{
					angle += 360.0f;
				}
			}
			// 左回転
			else if (moveLeft)
			{
				angle += 120.0f / (float)MoveFrame;
				if (angle >= 180.0f)
				{
					angle -= 360.0f;
				}
			}
			D3DXVECTOR3 curPos = transform->GetPosition();
			curPos.x = Distance * sinf(D3DXToRadian(angle));
			curPos.z = Distance * cosf(D3DXToRadian(angle));
			transform->SetPosition(curPos);
			counter++;
		}
		else
		{
			counter = 0;
			moveRight = false;
			moveLeft = false;
		}
	}
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
// テクスチャのセット
//=====================================
void SelectLogo::SetTextureIndex(const int& index)
{
	polygon->SetTextureIndex(index);
}

//=====================================
// 右に移動
//=====================================
void SelectLogo::TurnRight()
{
	if (!Moveable())
		return;
	moveRight = true;
}

//=====================================
// 左に移動
//=====================================
void SelectLogo::TurnLeft()
{
	if (!Moveable())
		return;
	moveLeft = true;
}

//=====================================
// 移動可否判定
//=====================================
bool SelectLogo::Moveable()
{
	return counter == 0 ? true : false;
}

//=====================================
// 角度のセット
//=====================================
void SelectLogo::SetAngle(float angle)
{
	this->angle = angle + 180.0f;
}
