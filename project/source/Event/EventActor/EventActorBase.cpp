//=====================================
//
// イベントアクター基底クラス[EventActorBase.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "EventActorBase.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
EventActorBase::EventActorBase(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag)
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();
	ResourceManager::Instance()->GetMesh(MeshTag, mesh);

	// ステータスセット
	transform->SetPosition(Pos);
	transform->SetScale(Scale);
	SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
EventActorBase::~EventActorBase()
{
	SAFE_DELETE(mesh);
}

//=====================================
// 更新
//=====================================
void EventActorBase::Update()
{
}

//=====================================
// 描画
//=====================================
void EventActorBase::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}