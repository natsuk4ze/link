//=====================================
//
// コンジェスティオンフィールドインフォステート[CongestionFieldInfoState.h]
// 機能：フィールドインフォアクターのステート（混雑している）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CONGESTIONFIELDINFOSTATE_H_
#define _CONGESTIONFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor::CongestionFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity)override;
	State OnUpdate(FieldInfoActor& entity)override;
};

#endif