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
	Tween::Scale(entity, D3DXVECTOR3(0.0f, 0.0f, 0.0f), entity.ActorScale, 120, OutCirc);
	entity.cntState = 0;
}

//=====================================
// 更新処理
//=====================================
PlaceActor::State PlaceActor::CreateActorState::OnUpdate(PlaceActor& entity)
{
	State current = State::Create;

	entity.cntState++;

	if (entity.cntState == 120)
	{
		entity.ChangeState(new IdleActorState());
		current = State::Idle;
		return current;
	}

	return current;
}