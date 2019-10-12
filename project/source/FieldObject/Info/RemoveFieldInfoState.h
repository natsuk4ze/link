//=====================================
//
// リムーブフィールドインフォステート[RemoveFieldInfoState.h]
// 機能：フィールドインフォアクターのステート（作成）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REMOVEFIELDINFOSTATE_H_
#define _REMOVEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor::RemoveFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity)override;
	State OnUpdate(FieldInfoActor& entity)override;
};

#endif