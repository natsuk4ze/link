//=====================================
//
// リムーブアクターステート[RemoveActorState.cpp]
// 機能：プレイスアクターのステート（削除）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RemoveActorState.h"

//=====================================
// 入場処理
//=====================================
void PlaceActor::RemoveActorState::OnStart(PlaceActor& entity)
{
	entity.current = Remove;
}

//=====================================
// 更新処理
//=====================================
PlaceActor::State PlaceActor::RemoveActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}