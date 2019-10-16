//=====================================
//
// アイドルアクターステート[IdleActorState.cpp]
// 機能：プレイスアクターのステート（待機）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "IdleActorState.h"

//=====================================
// 入場処理
//=====================================
void PlaceActor::IdleActorState::OnStart(PlaceActor& entity)
{
	entity.current = Idle;
}

//=====================================
// 更新処理
//=====================================
PlaceActor::State PlaceActor::IdleActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}