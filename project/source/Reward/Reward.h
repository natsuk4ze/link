//=====================================
//
// リワード[Reward.h]
// 機能：各リワードの基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _REWARD_H_
#define _REWARD_H_

#include "RewardController.h"
#include <string>

//**************************************
// クラス定義
//**************************************
class Reward
{
public:
	Reward(RewardController::Type type, int maxdata);
	~Reward();

	// 達成者の名前をセット
	void SetName(int BuffNo, int AlphabetNo);

	// 達成者の名前を確認
	int GetName(int BuffNo);

	// 今回のプレイで達成したかチェック
	bool CheckAchieved();

	// 達成者がすでにいるかチェック
	bool CheckFirstAchieved();

	// 達成をリセット
	void ResetAchieved();

	// データのセット
	virtual void SetData(int data) = 0;
	
	// データのリセット
	virtual void ResetData() = 0;

protected:
	RewardController::Type type;	// リワードの種類
	bool firstAchieve;				// 最初の到達確認
	bool achieve;					// 到達確認
	int name[3];					// 達成者の名前

	const int MaxData;
};

#endif
