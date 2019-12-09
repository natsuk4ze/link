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
#include <vector>

class Reward;
class Name;
namespace RC = RewardConfig;

//**************************************
// クラス定義
//**************************************
class RewardController :
	public BaseSingleton<RewardController>
{
	friend class BaseSingleton<RewardController>;
public:
	// **************開始、終了時*****************************
	// リワードの作成、削除
	void Create();
	void AllDelete();

	// **************ゲーム進行中******************************
	// 各リワードのデータをセット
	void SetRewardData(RC::Type rewardType, int data);

	// 各リワードの到達確認
	bool IsAchieved(RC::Type type);

	// **************リザルト画面用****************************
	// 全リワードの到達確認（達成したリワードのENUMを全て列挙して返す）
	std::vector<RC::Type> IsAllAchieved();

	// 全リワードなかからどれかひとつでも初達成のものがあるか
	bool FindFirstAchieved();

	// 今回のプレイで達成したリワードを全て達成済みにする（リザルト終了時）
	void SetFirstAchieved(const Name& name);

	// **************リワード確認画面用************************
	// 既に到達者がいるか（falseなら未達成）
	bool IsFirstAchieved(RC::Type rewardType);

	// リワード到達者の名前を確認
	Name* GetName(RC::Type rewardType);

	// **************ゲーム周回時************************
	// 全リワードのデータをリセット
	void ResetAllRewardData();

private:
	RewardController() {}
	~RewardController() {}

	std::map<RC::Type, Reward*> rewardPool;
};

#endif