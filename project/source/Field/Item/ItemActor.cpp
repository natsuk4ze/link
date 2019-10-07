//=====================================
//
// アイテムアクター[ItemActor.h]
// 機能：アイテムのアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "ItemActor.h"

const D3DXVECTOR2 ItemActor::ActorSize = D3DXVECTOR2(3.0f, 6.0f);
const float ItemActor::RotValue = 1.5f;

//=====================================
// コンストラクタ
//=====================================
ItemActor::ItemActor(const D3DXVECTOR3& pos)
{
	transform = new Transform();
	transform->SetPosition(pos);
	transform->Rotate(0.0f, 0.0f, 0.0f);
	this->SetSize(ActorSize);

	this->LoadTexture("data/TEXTURE/Item/Item.png");

	// 裏側作成
	D3DXQUATERNION rot = transform->GetRotation();
	reverse = new ReverseItemActor(transform->GetPosition(), D3DXVECTOR3(rot.x, rot.y, rot.z), ActorSize);
}

//=====================================
// デストラクタ
//=====================================
ItemActor::~ItemActor()
{
	SAFE_DELETE(transform);
	SAFE_DELETE(reverse);
}

//=====================================
// 更新
//=====================================
void ItemActor::Update()
{
	this->Rotate(RotValue);
	reverse->Update();
	reverse->Rotate(RotValue);
}

//=====================================
// 描画
//=====================================
void ItemActor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld(&mtxWorld);

	BoardPolygon::Draw();

	reverse->Draw();
}

//=====================================
// Y軸回転
//=====================================
void ItemActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// コンストラクタ
//=====================================
ReverseItemActor::ReverseItemActor(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR2& size)
{
	transform = new Transform();
	transform->SetPosition(D3DXVECTOR3(0.0f, 3.0f, 0.0f));
	transform->Rotate(0.0f, 90.0f, 0.0f);
	this->SetSize(size);

	this->LoadTexture("data/TEXTURE/Item/Item.png");
}

//=====================================
// デストラクタ
//=====================================
ReverseItemActor::~ReverseItemActor()
{
	SAFE_DELETE(transform);
}

//=====================================
// 更新
//=====================================
void ReverseItemActor::Update()
{
}

//=====================================
// 描画
//=====================================
void ReverseItemActor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld(&mtxWorld);

	BoardPolygon::Draw();
}

//=====================================
// Y軸回転
//=====================================
void ReverseItemActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}
