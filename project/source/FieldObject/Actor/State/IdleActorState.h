//=====================================
//
// アイドルアクターステート[IdleActorState.cpp]
// 機能：プレイスアクターのステート（待機）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _IDLEACTORSTATE_H_
#define _IDLEACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// クラス定義
//**************************************
class PlaceActor::IdleActorState :
	public PlaceActor::ActorState
{
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif

