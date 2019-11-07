//=====================================
//
// UFOアクター[UFOActor.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "UFOActor.h"

//=====================================
// コンストラクタ
//=====================================
UFOActor::UFOActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag) :
	EventActorBase(Pos, Scale, MeshTag)
{
}

//=====================================
// デストラクタ
//=====================================
UFOActor::~UFOActor()
{
}

//=====================================
// 更新
//=====================================
void UFOActor::Update()
{
	if (InHoverMotion)
	{
		FrameCount++;
		HoverMotion();
	}
}

//=====================================
// ホバリング運動の移動計算
//=====================================
void UFOActor::HoverMotion(void)
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
void UFOActor::SetHoverMotion(bool Flag)
{
	InHoverMotion = Flag;
	if (InHoverMotion)
	{
		BaseHoverPos = transform->GetPosition();
	}
}
