//=====================================
//
// クリエイトアクターステート[CreateActorState.cpp]
// 機能：プレイスアクターのステート（作成）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CreateActorState.h"
#include "../../../../Framework/Tween/Tween.h"
#include "IdleActorState.h"

//=====================================
// 入場処理
//=====================================
void PlaceActor::CreateActorState::OnStart(PlaceActor& entity)
{
	entity.current = Create;
}

//=====================================
// 更新処理
//=====================================
PlaceActor::State PlaceActor::CreateActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}