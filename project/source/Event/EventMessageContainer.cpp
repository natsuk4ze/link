//=============================================================================
//
// イベントメッセージコンテナクラス [EventMessageContainer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "EventMessageContainer.h"
#include "EventConfig.h"
#include "../Field/Place/PlaceConfig.h"

using namespace EventConfig;

//=============================================================================
// コンストラクタ
//=============================================================================
EventMessageContainer::EventMessageContainer()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
EventMessageContainer::~EventMessageContainer()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
void EventMessageContainer::GetEventMessage(int FieldLevel, int EventType, const char** MessagePtr)
{
	std::vector<const char*>MessageContainer;

	switch (EventType)
	{
		// ============================
		// 町の発展レベル上昇
		// ============================
	case CityLevelUp:

		if (FieldLevel == Field::Model::City)
		{
			MessageContainer.push_back("イベントメッセージ1");
			MessageContainer.push_back("イベントメッセージ2");
			MessageContainer.push_back("イベントメッセージ3");
			MessageContainer.push_back("イベントメッセージ4");
			MessageContainer.push_back("イベントメッセージ5");
		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 新しい町、国、星出現
		// ============================
	case NewCity:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 特殊なチップの使用回数回復
		// ============================
	case ChipRecovery:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 町に「有名人がいる状態」付与。数秒間発展スピード上昇
		// ============================
	case FamousPeople:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 全体にボーナス、特定の町に更にボーナス
		// ============================
	case Bonus:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// スロットを回してAI発展レベルにボーナス
		// ============================
	case AILevelUp:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 町の発展レベル減少
		// ============================
	case CityLevelDecrease:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 町消滅
		// ============================
	case CityDestroy:

		if (FieldLevel == Field::Model::City)
		{
			MessageContainer.push_back("町消滅イベントメッセージ1番だよ！");
			MessageContainer.push_back("町消滅イベントメッセージ2番だよ！");
			MessageContainer.push_back("町消滅イベントメッセージ3番だよ！");
		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// AI発展レベル減少
		// ============================
	case AILevelDecrease:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 操作反転（上下左右）
		// ============================
	case MoveInverse:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 一定時間特殊チップ使用不可
		// ============================
	case BanSpecialChip:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// 交差点の混雑度一定時間上昇
		// ============================
	case CongestionUp:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

	default:
		break;
	}

	if (!MessageContainer.empty())
	{
		int No = rand() % MessageContainer.size();
		*MessagePtr = MessageContainer.at(No);
	}
}


