//=====================================
//
// イベントアクター[EventActor.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "EventActor.h"
#include "../../Framework/Camera/ViewFrustum.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Resource/ResourceManager.h"


//=====================================
// コンストラクタ
//=====================================
EventActor::EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag) :
	onCamera(true)
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
EventActor::~EventActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// 更新
//=====================================
void EventActor::Update()
{
}

//=====================================
// 描画
//=====================================
void EventActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y軸回転
//=====================================
void EventActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// 座標のセット
//=====================================
void EventActor::SetPosition(const D3DXVECTOR3& Pos)
{
	transform->SetPosition(Pos);
}

//=====================================
// メッシュデータのカラー変更
//=====================================
void EventActor::SetColor(const D3DXCOLOR& Color)
{
	unsigned numMaterial = mesh->GetMaterialNum();

	for (unsigned i = 0; i < numMaterial; i++)
	{
		mesh->SetMaterialColor(Color, i);
	}
}

//=====================================
// 座標、回転、大きさをリセット
//=====================================
void EventActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//transform->SetScale(Scale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
