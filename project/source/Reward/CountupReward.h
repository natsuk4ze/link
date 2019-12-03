//=====================================
//
// カウントアップリワード[CountupReward.h]
// 機能：カウントアップするタイプのリワード
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _COUNTUPREWARD_H_
#define _COUNTUPREWARD_H_

#include "Reward.h"

//**************************************
// クラス定義
//**************************************
class CountupReward :
	public Reward
{
private:
	int data;

public:
	CountupReward(RC::Type type, int maxdata);
	~CountupReward();

	void SetData(int data)override;
	void ResetData()override;
};

#endif
