//=====================================
//
// フィールドインフォアクター[FieldInfoActor.cpp]
// 機能：フィールド上の情報を表示するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "FieldInfoActor.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 FieldInfoActor::ActorScale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

//=====================================
// コンストラクタ
//=====================================
FieldInfoActor::FieldInfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);

	polygon = new BoardPolygon();
	polygon->LoadTexture("data/TEXTURE/Info/Info.png");
	polygon->SetSize(D3DXVECTOR2(ActorScale.x, ActorScale.y));
}

//=====================================
// デストラクタ
//=====================================
FieldInfoActor::~FieldInfoActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// 更新
//=====================================
void FieldInfoActor::Update()
{
	if (!this->IsActive())
		return;;


}

//=====================================
// 描画
//=====================================
void FieldInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	polygon->Draw();

}