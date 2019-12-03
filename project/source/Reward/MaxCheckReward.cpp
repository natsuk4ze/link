//=====================================
//
// マックスチェックリワード[MaxCheckReward.h]
// 機能：最大値を超えたか確認するタイプのリワード
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "MaxCheckReward.h"

//=====================================
// コンストラクタ
//=====================================
MaxCheckReward::MaxCheckReward(RC::Type type, int maxdata) :
	Reward(type, maxdata), data(0)
{
}

//=====================================
// デストラクタ
//=====================================
MaxCheckReward::~MaxCheckReward()
{
}

//=====================================
// データの更新
//=====================================
void MaxCheckReward::SetData(int data)
{
	this->data = data;
	if (data >= MaxData)
	{
		achieve = true;
	}
}

//=====================================
// データのリセット
//=====================================
void MaxCheckReward::ResetData()
{
	this->data = 0;
	achieve = false;
}