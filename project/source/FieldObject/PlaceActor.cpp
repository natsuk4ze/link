//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos)
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();

	// ステータスセット
	transform->SetPosition(pos);
	SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// 更新
//=====================================
void PlaceActor::Update()
{
	this->PlayAnimation(animType);
}

//=====================================
// 描画
//=====================================
void PlaceActor::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y軸回転
//=====================================
void PlaceActor::Rotate(float y)
{
	D3DXQUATERNION rot = transform->GetRotation();
	transform->SetRotation(D3DXQUATERNION(rot.x, rot.y + (FLOAT)y, rot.z, rot.w));
}

//=====================================
// アニメーション再生
//=====================================
void PlaceActor::PlayAnimation(int AnimType)
{
	//switch (AnimType)
	//{
	//default:
	//	break;
	//}
}
