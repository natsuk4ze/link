//=====================================
//
// コネクトフィールドインフォステート[ConnectFieldInfoState.cpp]
// 機能：フィールドインフォアクターのステート（道がつながった）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "ConnectFieldInfoState.h"

//=====================================
// 入場処理
//=====================================
void FieldInfoActor::ConnectFieldInfoState::OnStart(FieldInfoActor& entity)
{

}

//=====================================
// 更新処理
//=====================================
FieldInfoActor::State FieldInfoActor::ConnectFieldInfoState::OnUpdate(FieldInfoActor& entity)
{
	return State::Idle;
}