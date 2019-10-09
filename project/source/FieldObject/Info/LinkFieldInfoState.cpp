//=====================================
//
// リンクフィールドインフォステート[LinkFieldInfoState.cpp]
// 機能：フィールドインフォアクターのステート（リンクレベルが上った）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "LinkFieldInfoState.h"

//=====================================
// 入場処理
//=====================================
void FieldInfoActor::LinkFieldInfoState::OnStart(FieldInfoActor& entity)
{

}

//=====================================
// 更新処理
//=====================================
FieldInfoActor::State FieldInfoActor::LinkFieldInfoState::OnUpdate(FieldInfoActor& entity)
{
	return State::Idle;
}