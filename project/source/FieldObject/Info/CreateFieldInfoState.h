//=====================================
//
// クリエイトフィールドインフォステート[CreateFieldInfoState.h]
// 機能：フィールドインフォアクターのステート（作成）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CREATEFIELDINFOSTATE_H_
#define _CREATEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor::CreateFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif