//=====================================
//
// コネクトフィールドインフォステート[ConnectFieldInfoState.h]
// 機能：フィールドインフォアクターのステート（道がつながった）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CONNECTFIELDINFOSTATE_H_
#define _CONNECTEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor::ConnectFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif