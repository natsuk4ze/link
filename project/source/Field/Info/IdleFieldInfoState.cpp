//=====================================
//
// アイドルフィールドインフォステート[IdleFieldInfoState.cpp]
// 機能：フィールドインフォアクターのステート（待機）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "IdleFieldInfoState.h"

//=====================================
// 入場処理
//=====================================
void FieldInfoActor::IdleFieldInfoState::OnStart(FieldInfoActor& entity)
{

}

//=====================================
// 更新処理
//=====================================
FieldInfoActor::State FieldInfoActor::IdleFieldInfoState::OnUpdate(FieldInfoActor& entity)
{
	return State::Idle;
}