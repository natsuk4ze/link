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
const D3DXVECTOR2 InfoActor::ViewerWorldSize = D3DXVECTOR2(5.0f, 5.0f);
const DWORD InfoActor::ViewerCanvasSize = 256;

//=====================================
// コンストラクタ
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);

	// ビューアの作成
	viewer = new Viewer3D(ViewerCanvasSize, ViewerCanvasSize, ViewerWorldSize);
	viewer->SetPosition(D3DXVECTOR3(pos));
}

//=====================================
// デストラクタ
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(viewer);
}