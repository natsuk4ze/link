//=====================================
//
//FieldGround.cpp
//機能:フィールド地面
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldGround.h"

/**************************************
コンストラクタ
***************************************/
FieldGround::FieldGround()
{
	LoadTexture("data/TEXTURE/Field/Ground.jpg");
	
	const D3DXVECTOR2 FieldSize{ 10000.0f, 10000.0f };
	const D3DXVECTOR2 TextureLoop{ 500.0f, 500.0f };
	SetSize(FieldSize);
	SetUV(TextureLoop);

	transform->Rotate(90.0f, 0.0f, 0.0f);
}

/**************************************
デストラクタ
***************************************/
FieldGround::~FieldGround()
{
}

/**************************************
描画処理
***************************************/
void FieldGround::Draw()
{
	transform->SetWorld();
	BoardPolygon::Draw();
}
