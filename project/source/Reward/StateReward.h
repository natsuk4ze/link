//=====================================
//
// ステートリワード[StateReward.h]
// 機能：いくつかの状態を確認するタイプのリワード
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _STATEREWARD_H_
#define _STATEREWARD_H_

#include "Reward.h"
#include <vector>

//**************************************
// クラス定義
//**************************************
class StateReward :
	public Reward
{
private:
	std::vector<int> data;

public:
	StateReward(RewardController::Type type, int maxdata);
	~StateReward();

	void SetData(int data)override;
	void ResetData()override;

};

#endif
