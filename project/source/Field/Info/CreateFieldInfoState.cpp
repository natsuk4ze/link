//=====================================
//
// クリエイトフィールドインフォステート[CreateFieldInfoState.cpp]
// 機能：フィールドインフォアクターのステート（作成）
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CreateFieldInfoState.h"

//=====================================
// 入場処理
//=====================================
void FieldInfoActor::CreateFieldInfoState::OnStart(FieldInfoActor& entity)
{

}

//=====================================
// 更新処理
//=====================================
FieldInfoActor::State FieldInfoActor::CreateFieldInfoState::OnUpdate(FieldInfoActor& entity)
{
	return State::Idle;
}