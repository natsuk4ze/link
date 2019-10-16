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

	switch (entity.type)
	{
	case FModel::Road:
		break;
	case FModel::Town:
		break;
	case FModel::Junction:
			//Tween::Move(entity, entity.GetPosition() + D3DXVECTOR3(0.0f, 30.0f, 0.0f), entity.GetPosition(), 60, OutCirc);
		Tween::Rotate(entity, entity.GetRotation() + D3DXVECTOR3(0.0f, 180.0f, 0.0f), entity.GetRotation(), 60, OutCirc);
		Tween::Scale(entity, D3DXVECTOR3(0.0f, 0.0f, 0.0f), entity.ActorScale, 60, OutCirc, [&entity]
		{
			// コールバックで現在のステートをアイドルに変更してTweenを終了する
			entity.ChangeState(new IdleActorState());
			//entity.state = Idle;
		});
		break;
	case FModel::Bridge:
		break;
	case FModel::Mountain:
		break;
	case FModel::River:
		break;
	default:
		break;
	}
}

//=====================================
// 更新処理
//=====================================
PlaceActor::State PlaceActor::CreateActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}