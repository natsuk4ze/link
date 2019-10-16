//=====================================
//
// リバーアクター[RiverActor.cpp]
// 機能：川（時空断裂）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RiverActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "State/CreateActorState.h"

//=====================================
// コンストラクタ
//=====================================
RiverActor::RiverActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		//ResourceManager::Instance()->GetMesh("River-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::River;

	// テスト
	state = new CreateActorState();
	state->OnStart(*this);
}

//=====================================
// デストラクタ
//=====================================
RiverActor::~RiverActor()
{
}
