//=====================================
//
// リワードコントローラ[RewardController.h]
// 機能：各リワードをコントロールするクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RewardController.h"
#include "Reward.h"
#include "CountupReward.h"
#include "StateReward.h"

//**************************************
// スタティックメンバ初期化
//**************************************
const int RewardController::MaxData[] = {
	3, 20, 15, 15, 10, 20, 250, 10000, 7, 4
};

//=====================================
// データ作成
//=====================================
void RewardController::Create(Type type, int maxData)
{
	if (rewardPool.count(type) == 0)
	{
		if (type == MinusComplete || type == PlusComplete)
		{
			Reward* reward = new StateReward(type, maxData);
			rewardPool.emplace(type, reward);
		}
		else
		{
			Reward* reward = new CountupReward(type, maxData);
			rewardPool.emplace(type, reward);
		}
	}
	else
	{
		char message[64];
		MessageBox(0, message, "This reward already exists", 0);
	}
}

//=====================================
// データ全削除
//=====================================
void RewardController::AllDelete()
{
	for (auto& reward : rewardPool)
	{
		SAFE_DELETE(reward.second);
	}
	rewardPool.clear();
}

//=====================================
// 到達確認
//=====================================
bool RewardController::CheckAchieved(Type rewardType)
{
	return rewardPool[rewardType]->CheckAchieved();
}

//=====================================
// 到達確認
//=====================================
bool RewardController::CheckFirstAchieved(Type rewardType)
{
	return rewardPool[rewardType]->CheckFirstAchieved();
}

//=====================================
// 名前の取得（一文字ずつ）
//=====================================
int RewardController::GetName(Type rewardType, int alphabetNo)
{
	return rewardPool[rewardType]->GetName(alphabetNo);
}

//=====================================
// データのセット
//=====================================
void RewardController::SetRewardData(Type rewardType, int data)
{
	rewardPool[rewardType]->SetData(data);
}

//=====================================
// データのリセット
//=====================================
void RewardController::ResetRewardData()
{
	for (auto& reward : rewardPool)
	{
		reward.second->ResetAchieved();
		reward.second->ResetData();
	}
}
