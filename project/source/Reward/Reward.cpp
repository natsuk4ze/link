//=====================================
//
// リワード[Reward.h]
// 機能：各リワードの基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "Reward.h"
#include "../Viewer/NameViewer/Name.h"

//=====================================
// コンストラクタ
//=====================================
Reward::Reward(RC::Type type, int maxdata) :
	type(type), achieve(false), firstAchieve(false), name(), MaxData(maxdata)
{
	name = new Name();
}

//=====================================
// デストラクタ
//=====================================
Reward::~Reward()
{
	SAFE_DELETE(name);
}

//=====================================
// 名前のセット
//=====================================
void Reward::SetName(const Name& name)
{
	this->name = new Name(name);
	firstAchieve = true;
}

//=====================================
// 名前の取得
//=====================================
Name* Reward::GetName()
{
	return name;
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
