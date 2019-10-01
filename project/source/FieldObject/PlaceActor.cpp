//=====================================
//
// プレイスアクター[PlaceActor.cpp]
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
	container->Create();
	container->Load("data/MODEL/transform.x");
	//ResourceManager::Instance()->GetMesh("tag", container);

	// ステータスセット
	transform->SetPosition(pos);
	SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
PlaceActor::~PlaceActor()
{
	container->Release();
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
	container->Draw();
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
