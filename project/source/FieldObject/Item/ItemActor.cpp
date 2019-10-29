//=====================================
//
// アイテムアクター[ItemActor.h]
// 機能：アイテムのアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "ItemActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

const D3DXVECTOR2 ItemActor::ActorSize = D3DXVECTOR2(3.0f, 6.0f);
const float ItemActor::RotValue = 1.5f;

//=====================================
// コンストラクタ
//=====================================
ItemActor::ItemActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->Rotate(0.0f, 0.0f, 0.0f);

	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("ItemActor", polygon);

	//this->SetSize(ActorSize);
	//this->LoadTexture("data/TEXTURE/Item/Item.png");
}

//=====================================
// デストラクタ
//=====================================
ItemActor::~ItemActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// 初期化
//=====================================
void ItemActor::Init()
{
	ResourceManager::Instance()->MakePolygon("ItemActor", "data/TEXTURE/Item/Item.png", ActorSize);
}

//=====================================
// 更新
//=====================================
void ItemActor::Update()
{
	this->Rotate(RotValue);
}

//=====================================
// 描画
//=====================================
void ItemActor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//裏面も描画したいので背面カリングを切る
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	polygon->Draw(transform->GetMatrix());

	//背面カリングを元に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=====================================
// Y軸回転
//=====================================
void ItemActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}