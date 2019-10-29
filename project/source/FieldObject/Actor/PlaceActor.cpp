//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../Animation/ActorAnimation.h"
#include "../../../Framework/Camera/ViewFrustum.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../Field/PlaceActorController.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PlaceActor::Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel) :
	onCamera(true)
{
	// メッシュコンテナの作成
	mesh = MeshContainer::Create();

	// ステータスセット
	transform->SetPosition(pos);
	transform->SetScale(Scale);
	this->SetActive(true);
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
	// カリング判定
	onCamera = Camera::MainCamera()->GetViewFrustrum().CheckOnCamera(transform->GetPosition(), Field::Actor::PlaceActorController::PlacePositionOffset);

#if _DEBUG
	Debug();
#endif
}

//=====================================
// 描画
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	if (!onCamera)
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y軸回転
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// 座標のセット
//=====================================
void PlaceActor::SetPosition(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
}

//=====================================
// メッシュデータのカラー変更
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color)
{
	unsigned numMaterial = mesh->GetMaterialNum();

	for (unsigned i = 0; i < numMaterial; i++)
	{
		mesh->SetMaterialColor(color, i);
	}
}

//=====================================
// 座標、回転、大きさをリセット
//=====================================
void PlaceActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	transform->SetScale(Scale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=====================================
// デバッグ
//=====================================
#if _DEBUG
void PlaceActor::Debug()
{
	Debug::Begin("PlaceActor", false);
	Debug::Text("ChangeAnimation");
	Debug::NewLine();
	if (Debug::Button("Fall"))
	{
		ActorAnimation::FallAndExpantion(*this);
	}
	Debug::NewLine();
	if (Debug::Button("RotateAndExpantion"))
	{
		ActorAnimation::RotateAndExpantion(*this);
	}
	Debug::NewLine();
	if (Debug::Button("RotateAndShrink"))
	{
		ActorAnimation::RotateAndShrink(*this);
	}
	Debug::NewLine();
	if (Debug::Button("ExpantionYAndReturnToOrigin"))
	{
		ActorAnimation::ExpantionYAndReturnToOrigin(*this);
	}
	Debug::NewLine();
	if (Debug::Button("ResetScale"))
	{
		transform->SetScale(Scale);
	}
	Debug::NewLine();
	Debug::Text("OnCamera = %s", onCamera ? "true" : "false");
	if (Debug::Button("OnCamera"))
	{
		onCamera ? onCamera = false : onCamera = true;
	}
	Debug::End();
}
#endif
