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
#include "MaxCheckReward.h"

//=====================================
// データ作成
//=====================================
void RewardController::Create(RC::Type type, int maxData)
{
	if (rewardPool.count(type) == 0)
	{
		if (type == RC::MinusComplete || type == RC::PlusComplete)
		{
			Reward* reward = new StateReward(type, maxData);
			rewardPool.emplace(type, reward);
		}
		else if (type == RC::Linker || type == RC::MasterAI)
		{
			Reward* reward = new MaxCheckReward(type, maxData);
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
bool RewardController::CheckAchieved(RC::Type rewardType)
{
	return rewardPool[rewardType]->CheckAchieved();
}

//=====================================
// 到達確認
//=====================================
bool RewardController::CheckFirstAchieved(RC::Type rewardType)
{
	return rewardPool[rewardType]->CheckFirstAchieved();
}

//=====================================
// 名前の取得（一文字ずつ）
//=====================================
int RewardController::GetName(RC::Type rewardType, int alphabetNo)
{
	return rewardPool[rewardType]->GetName(alphabetNo);
}

//=====================================
// データのセット
//=====================================
void RewardController::SetRewardData(RC::Type rewardType, int data)
{
	rewardPool[rewardType]->SetData(data);
}

//=====================================
// データのリセット
//=====================================
void RewardController::ResetAllRewardData()
{
	for (auto& reward : rewardPool)
	{
		reward.second->ResetAchieved();
		reward.second->ResetData();
	}
}
