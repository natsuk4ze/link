//=====================================
//
// リムーブアクターステート[RemoveActorState.h]
// 機能：プレイスアクターのステート（削除）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REMOVEACTORSTATE_H_
#define _REMOVEACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// クラス定義
//**************************************
class PlaceActor::RemoveActorState :
	public PlaceActor::ActorState
{
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif
