//=============================================================================
//
// 混雑度上昇イベントクラス [CongestionUpEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "CongestionUpEvent.h"
#include "../EventConfig.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float CongestionBias = 1.0f;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
CongestionUpEvent::CongestionUpEvent(int RemainTime) : RemainTime(RemainTime)
{
	fieldController->RaiseTrafficJam(CongestionBias);
}

//=============================================================================
// デストラクタ
//=============================================================================
CongestionUpEvent::~CongestionUpEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void CongestionUpEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		fieldController->RaiseTrafficJam(0.0f);
		UseFlag = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CongestionUpEvent::Draw()
{
	
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string CongestionUpEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("交差点混雑度上昇イベント");
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
