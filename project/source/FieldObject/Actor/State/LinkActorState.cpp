//=====================================
//
// リンクアクターステート[LinkActorState.cpp]
// 機能：プレイスアクターのステート（道がつながった）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "LinkActorState.h"

//=====================================
// 入場処理
//=====================================
void PlaceActor::LinkActorState::OnStart(PlaceActor& entity)
{

}

//=====================================
// 更新処理
//=====================================
PlaceActor::State PlaceActor::LinkActorState::OnUpdate(PlaceActor& entity)
{
	return State::Idle;
}