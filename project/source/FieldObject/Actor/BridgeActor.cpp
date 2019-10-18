//=====================================
//
// ブリッジアクター[BridgeActor.cpp]
// 機能：橋（ワープホール）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "BridgeActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"

//=====================================
// コンストラクタ
//=====================================
BridgeActor::BridgeActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("Bridge-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::Bridge;
}

//=====================================
// デストラクタ
//=====================================
BridgeActor::~BridgeActor()
{
}