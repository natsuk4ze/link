//=====================================
//
// リンクアクターステート[LinkActorState.h]
// 機能：プレイスアクターのステート（道がつながった）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _LINKACTORSTATE_H_
#define _LINKACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// クラス定義
//**************************************
class PlaceActor::LinkActorState :
	public PlaceActor::ActorState
{
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif
