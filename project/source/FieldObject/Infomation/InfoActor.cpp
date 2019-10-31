//=====================================
//
// インフォアクター[InfoActor.cpp]
// 機能：フィールド上に情報を表示するための基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "InfoActor.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Camera/ViewFrustum.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const float InfoActor::ActorSize = 10.0f;

//=====================================
// コンストラクタ
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// 更新
//=====================================
void InfoActor::Update()
{
	if (!this->IsActive())
		return;

	//onCamera = Camera::MainCamera()->GetViewFrustrum().CheckOnCamera(transform->GetPosition(), ActorSize);

}

//=====================================
// 描画
//=====================================
void InfoActor::Draw()
{
	if (!this->IsActive())
		return;

	//if (!onCamera)
	//	return;

	polygon->Draw(transform->GetMatrix());

}
