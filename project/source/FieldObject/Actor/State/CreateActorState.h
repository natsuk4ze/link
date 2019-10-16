//=====================================
//
// クリエイトアクターステート[CreateActorState.h]
// 機能：プレイスアクターのステート（作成）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CREATEACTORSTATE_H_
#define _CREATEACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// クラス定義
//**************************************
class PlaceActor::CreateActorState :
	public PlaceActor::ActorState
{
	friend class Tween;
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif
