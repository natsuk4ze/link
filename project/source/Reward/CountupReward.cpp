//=====================================
//
// カウントアップリワード[CountupReward.cpp]
// 機能：カウントアップするタイプのリワード
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CountupReward.h"

//=====================================
// コンストラクタ
//=====================================
CountupReward::CountupReward(RC::Type type, int maxdata) :
	Reward(type, maxdata), data(0)
{
}

//=====================================
// デストラクタ
//=====================================
CountupReward::~CountupReward()
{
}

//=====================================
// データのセット
//=====================================
void CountupReward::SetData(int data)
{
	if (this->data < MaxData)
	{
		this->data += data;
		if (this->data >= MaxData)
		{
			achieve = true;
		}
	}
}

//=====================================
// データのリセット
//=====================================
void CountupReward::ResetData()
{
	data = 0;
	achieve = false;
}

