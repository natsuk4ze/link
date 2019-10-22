//=====================================
//
// ノンアクター[NoneActor.cpp]
// 機能：何もアクターがない状態を表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "NoneActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
NoneActor::NoneActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	ResourceManager::Instance()->GetMesh("NoneActor", mesh);
	type = FModel::None;
}

//=====================================
// デストラクタ（メッシュの開放は基底クラスで）
//=====================================
NoneActor::~NoneActor()
{
}