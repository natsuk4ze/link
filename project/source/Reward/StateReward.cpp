//=====================================
//
// ステートリワード[StateReward.cpp]
// 機能：いくつかの状態を確認するタイプのリワード
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "StateReward.h"

//=====================================
// コンストラクタ
//=====================================
StateReward::StateReward(RewardController::Type type, int maxdata) :
	Reward(type, maxdata)
{
	for (int i = 0; i < MaxData; i++)
	{
		data.push_back(0);
	}
}

//=====================================
// デストラクタ
//=====================================
StateReward::~StateReward()
{
	data.clear();
}

//=====================================
// データのセット
//=====================================
void StateReward::SetData(int data)
{
	this->data[data] = 1;

}

//=====================================
// データのリセット
//=====================================
void StateReward::ResetData()
{
	for (auto& i : data)
	{
		i = 0;
	}
}