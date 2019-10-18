//=============================================================================
//
// AIレベル上昇イベントクラス [AILevelUpEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "AILevelUpEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int AILevelUpNum = 1;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
AILevelUpEvent::AILevelUpEvent()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
AILevelUpEvent::~AILevelUpEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void AILevelUpEvent::Update()
{
	fieldController->AdjustLevelAI(AILevelUpNum);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void AILevelUpEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string AILevelUpEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("このドリルは天を貫くドリルだ！！");
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
