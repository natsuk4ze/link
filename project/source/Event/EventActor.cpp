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
EventActor::EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag)
{
	// メッシュコンテナの作成
	mesh = new MeshContainer();
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
	SAFE_DELETE(mesh);
}

//=====================================
// 更新
//=====================================
void EventActor::Update()
{
	if (InHoverMotion)
	{
		FrameCount++;
		HoverMotion();
	}
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
// ホバリング運動の移動計算
//=====================================
void EventActor::HoverMotion(void)
{
	// 運動範囲
	D3DXVECTOR3 Radius = D3DXVECTOR3(0.6f, 0.6f, 0.5f);
	D3DXVECTOR3	Offset = D3DXVECTOR3(20.0f, 10.0f, 30.0f);
	// 運動速度
	D3DXVECTOR3	Rate = D3DXVECTOR3(3.0f, 5.0f, 5.0f);
	D3DXVECTOR3	Theta = D3DXVECTOR3
	(
		D3DXToRadian(Rate.x * FrameCount + Offset.x),
		D3DXToRadian(Rate.y * FrameCount + Offset.y),
		D3DXToRadian(Rate.z * FrameCount + Offset.z)
	);

	D3DXVECTOR3 hover = D3DXVECTOR3
	(
		Radius.x * sinf(Theta.x),
		Radius.y * sinf(Theta.y),
		Radius.z * sinf(Theta.z)
	);

	transform->SetPosition(BaseHoverPos + hover);
}

//=====================================
// ホバリング運動フラグ設置
//=====================================
void EventActor::SetHoverMotion(bool Flag)
{
	InHoverMotion = Flag;
	if (InHoverMotion)
	{
		BaseHoverPos = transform->GetPosition();
	}
}
