//=============================================================================
//
// 町発展度ボーナスイベントクラス [BonusEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "BonusEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
BonusEvent::BonusEvent()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
BonusEvent::~BonusEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void BonusEvent::Update()
{
	//fieldController->SetDevelopSpeedBonus();
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void BonusEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string BonusEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("ラッキーセブン！");
	}
	else if (FieldLevel == Field::Model::World)
	{

	}
	else if (FieldLevel == Field::Model::Space)
	{

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
