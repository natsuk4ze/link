//=====================================
//
// アイドルフィールドインフォステート[IdleFieldInfoState.h]
// 機能：フィールドインフォアクターのステート（待機）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _IDLEFIELDINFOSTATE_H_
#define _IDLEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor::IdleFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif