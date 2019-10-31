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
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// スタティックメンバ初期化
//**************************************
const float InfoActor::ActorSize = 5.0f;

//=====================================
// コンストラクタ
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);

	// ビューアの作成
	viewer = new Viewer3D(256, 256, D3DXVECTOR2(ActorSize, ActorSize));
	viewer->SetPosition(D3DXVECTOR3(pos));
}

//=====================================
// デストラクタ
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(viewer);
}