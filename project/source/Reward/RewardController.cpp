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
#include <algorithm>

//=====================================
// データ作成
//=====================================
void RewardController::Create()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (rewardPool.count(RC::Type(i)) == 0)
		{
			if (RC::Type(i) == RC::MinusComplete || RC::Type(i) == RC::PlusComplete)
			{
				Reward* reward = new StateReward(RC::Type(i), RC::MaxData[i]);
				rewardPool.emplace(RC::Type(i), reward);
			}
			else if (RC::Type(i) == RC::Linker || RC::Type(i) == RC::MasterAI)
			{
				Reward* reward = new MaxCheckReward(RC::Type(i), RC::MaxData[i]);
				rewardPool.emplace(RC::Type(i), reward);
			}
			else
			{
				Reward* reward = new CountupReward(RC::Type(i), RC::MaxData[i]);
				rewardPool.emplace(RC::Type(i), reward);
			}
		}
		else
		{
			char message[64];
			MessageBox(0, message, "This reward already exists", 0);
		}
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
std::vector<RC::Type> RewardController::GetAllAchieved()
{
	std::vector<RC::Type> ret;

	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (rewardPool[RC::Type(i)]->CheckAchieved())
		{
			ret.push_back(RC::Type(i));
		}
	}

	return ret;
}

//=====================================
// 到達確認
//=====================================
bool RewardController::ExistFirstAchieved()
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (rewardPool[RC::Type(i)]->CheckAchieved())
		{
			if (!rewardPool[RC::Type(i)]->CheckFirstAchieved())
				return true;
		}
	}
	return false;

	/*auto itr = std::find_if(rewardPool.begin(), rewardPool.end(), [](std::pair<RC::Type, Reward*> a) {
		return a.second->CheckFirstAchieved(); 
	});

	if (itr == rewardPool.end())
	{
		return false;
	}
	else
	{
		return true;
	}*/
}

//=====================================
// 到達確認
//=====================================
bool RewardController::IsAchieved(RC::Type type)
{
	return rewardPool[type]->CheckAchieved();
}

//=====================================
// 到達確認
//=====================================
bool RewardController::IsFirstAchieved(RC::Type rewardType)
{
	return rewardPool[rewardType]->CheckFirstAchieved();
}

//=====================================
// 到達したデータをセット
//=====================================
void RewardController::SetFirstAchieved(const Name& name)
{
	for (int i = 0; i < RC::Type::Max; i++)
	{
		if (rewardPool[RC::Type(i)]->CheckFirstAchieved())
		{
			rewardPool[RC::Type(i)]->SetName(name);
		}
	}
}

//=====================================
// 名前の取得
//=====================================
Name* RewardController::GetName(RC::Type rewardType)
{
	return rewardPool[rewardType]->GetName();
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
