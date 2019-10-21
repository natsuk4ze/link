//=============================================================================
//
// 制限時間回復イベントクラス [TimeRecoveryEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "TimeRecoveryEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int RecoveryFrame = 150;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
TimeRecoveryEvent::TimeRecoveryEvent()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
TimeRecoveryEvent::~TimeRecoveryEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void TimeRecoveryEvent::Update()
{
	fieldEventHandler->AddRemainTime(RecoveryFrame);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void TimeRecoveryEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string TimeRecoveryEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("制限時間回復！");
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
