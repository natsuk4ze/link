//=====================================
//
// リンクフィールドインフォステート[LinkFieldInfoState.h]
// 機能：フィールドインフォアクターのステート（リンクレベルが上がった）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _LINKFIELDINFOSTATE_H_
#define _LINKFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// クラス定義
//**************************************
class FieldInfoActor::LinkFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif