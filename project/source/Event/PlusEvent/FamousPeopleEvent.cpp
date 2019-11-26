//=============================================================================
//
// 有名人イベントクラス [FamousPeopleEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "FamousPeopleEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ボーナス数値
const float BonusNum = 1.5f;
// デフォルトのボーナス効果フレーム
const int DefalutBonusFrame = 150;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
FamousPeopleEvent::FamousPeopleEvent() :
	EventBase(false),
	RemainTime(DefalutBonusFrame)
{
	fieldEventHandler->SetDevelopBonus(BonusNum);
}

//=============================================================================
// デストラクタ
//=============================================================================
FamousPeopleEvent::~FamousPeopleEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void FamousPeopleEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		// ボーナス停止処理
		fieldEventHandler->SetDevelopBonus(1.0f);

		UseFlag = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void FamousPeopleEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string FamousPeopleEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::City)
	{
		MessageContainer.push_back("芸人が街に来た！\n発展速度アップ！");
	}
	else if (FieldLevel == Field::World)
	{
		MessageContainer.push_back("芸人が街に来た！\n発展速度アップ！");
	}
	else if (FieldLevel == Field::Space)
	{
		MessageContainer.push_back("芸人が街に来た！\n発展速度アップ！");
	}

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "イベントメッセージがありません";
		return ErrMsg;
	}
}
