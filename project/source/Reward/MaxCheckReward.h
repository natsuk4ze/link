//=====================================
//
// マックスチェックリワード[MaxCheckReward.h]
// 機能：最大値を超えたか確認するタイプのリワード
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _MAXCHECKREWARD_H_
#define _MAXCHECKREWARD_H_

#include "Reward.h"

//**************************************
// クラス定義
//**************************************
class MaxCheckReward :
	public Reward
{
private:
	int data;
public:
	MaxCheckReward(RewardController::Type type, int maxdata);
	~MaxCheckReward();

	void SetData(int data)override;
	void ResetData()override;

};

#endif
