//=====================================
//
// リワード[Reward.h]
// 機能：各リワードの基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "Reward.h"

//=====================================
// コンストラクタ
//=====================================
Reward::Reward(RewardController::Type type, int maxdata) :
	type(type), achieve(false), firstAchieve(false), name(), MaxData(maxdata)
{
}

//=====================================
// デストラクタ
//=====================================
Reward::~Reward()
{
}

//=====================================
// 名前のセット
//=====================================
void Reward::SetName(int BuffNo, int AlphabetNo)
{
	this->name[BuffNo] = AlphabetNo;
}

//=====================================
// 名前の取得
//=====================================
int Reward::GetName(int BuffNo)
{
	return this->name[BuffNo];
}

//=====================================
// 達成確認
//=====================================
bool Reward::CheckAchieved()
{
	return this->achieve;
}

//=====================================
// 達成確認
//=====================================
bool Reward::CheckFirstAchieved()
{
	return this->firstAchieve;
}

//=====================================
// 達成のリセット
//=====================================
void Reward::ResetAchieved()
{
	this->achieve = false;
}
