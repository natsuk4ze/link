//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"
#include "../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();

	// ステータスセット
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
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
	if (!IsActive())
		return;

	if (!animActive)
		return;

	switch (animType)
	{
	case FActor::Create:
		break;
	case FActor::Remove:
		break;
	default:
		break;
	}
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
// アニメーションを再生させる
//=====================================
void PlaceActor::PlayAnimation(FActor::AnimType AnimType)
{
	this->animType = AnimType;
	this->animActive = true;
}

//=====================================
// メッシュデータのカラー変更
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color, UINT index)
{
	mesh->SetMaterialColor(color, index);
}