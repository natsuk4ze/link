//=====================================
//
// リワードコントローラ[RewardController.h]
// 機能：各リワードをコントロールするクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REWARDCONTROLLER_H_
#define _REWARDCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"
#include "RewardConfig.h"
#include <map>
#include <string>

class Reward;
namespace RC = RewardConfig;

//**************************************
// クラス定義
//**************************************
class RewardController :
	public BaseSingleton<RewardController>
{
	friend class BaseSingleton<RewardController>;
public:
	// リワードの作成、削除
	void Create(RC::Type type, int maxData);
	void AllDelete();

	// 各リワードの到達確認
	bool CheckAchieved(RC::Type rewardType);
	bool CheckFirstAchieved(RC::Type rewardType);

	// リワード到達者の名前を確認（一文字ずつ）
	int GetName(RC::Type rewardType, int alphabetNo);

	// 各リワードのデータをセット
	void SetRewardData(RC::Type rewardType, int data);

	// 全リワードのデータをリセット
	void ResetAllRewardData();

private:
	RewardController() {}
	~RewardController() {}

	std::map<RC::Type, Reward*> rewardPool;
};

#endif