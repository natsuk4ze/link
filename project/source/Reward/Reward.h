//=====================================
//
// リワード[Reward.h]
// 機能：各リワードの基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REWARD_H_
#define _REWARD_H_

#include "../../main.h"
#include <string>
#include "RewardConfig.h"
namespace RC = RewardConfig;
class Name;
//**************************************
// クラス定義
//**************************************
class Reward
{
public:
	Reward(RC::Type type, int maxdata);
	~Reward();

	// 達成者の名前をセット
	void SetName(const Name& name);

	// 達成者の名前を確認
	Name* GetName();

	// 今回のプレイで達成したかチェック
	bool CheckAchieved();

	// 達成者がすでにいるかチェック
	bool CheckFirstAchieved();

	//今回のプレイで初達成したかどうか
	bool IsAchievedThisTime() const;

	// 達成をリセット
	void ResetAchieved();

	// データのセット
	virtual void SetData(int data) = 0;
	
	// データのリセット
	virtual void ResetData() = 0;

	// セーブデータの読み込み
	void LoadData(bool flag);

protected:
	RC::Type type;	// リワードの種類
	bool firstAchieve;				// 最初の到達確認
	bool achieve;					// 到達確認
	Name* name;						// 達成者の名前

	const int MaxData;
};

#endif
