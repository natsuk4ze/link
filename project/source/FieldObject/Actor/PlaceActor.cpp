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
#include "../../../Framework/Camera/ViewFrustrum.h"
#include "../../../Framework/Camera/Camera.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

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
	transform->SetScale(ActorScale);
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
	if (!CheckOnCamera())
		return;

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
void PlaceActor::SetColor(const D3DXCOLOR& color, UINT index)
{
	mesh->SetMaterialColor(color, index);
}

//=====================================
// 座標、回転、大きさをリセット
//=====================================
void PlaceActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	transform->SetScale(ActorScale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=====================================
// カメラ内判定
//=====================================
bool PlaceActor::CheckOnCamera()
{
	D3DXVECTOR3 obj = transform->GetPosition();

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 nor = Camera::MainCamera()->GetViewFrustrum().GetNormal(ViewFrustrum::Surface(i));
		D3DXVECTOR3 vec = obj - Camera::MainCamera()->GetViewFrustrum().GetSurfacePoint(ViewFrustrum::Surface(i));

		// 視錐台の法線と、視錐台からオブジェクトへのベクトルから内積計算
		float dot = D3DXVec3Dot(&nor, &vec);

		if (dot > 0)
		{
			onCamera = true;
		}
		else
		{
			// 1つでもfalseならリターン
			onCamera = false;
			break;
		}

	}

	return onCamera;
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
		transform->SetScale(ActorScale);
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
