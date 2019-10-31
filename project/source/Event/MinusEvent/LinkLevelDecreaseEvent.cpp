//=============================================================================
//
// リンクレベル減少イベントクラス [LinkLevelDecreaseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "LinkLevelDecreaseEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int LinkLevelDecreaseNum = -1;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
LinkLevelDecreaseEvent::LinkLevelDecreaseEvent() :
	EventBase(false)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
LinkLevelDecreaseEvent::~LinkLevelDecreaseEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void LinkLevelDecreaseEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelDecreaseNum);
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void LinkLevelDecreaseEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string LinkLevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("リンクレベル減らすイベント");
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
