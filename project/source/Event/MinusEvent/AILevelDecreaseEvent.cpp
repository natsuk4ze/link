//=============================================================================
//
// AIレベル減少イベントクラス [AILevelDecreaseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "AILevelDecreaseEvent.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float DecreasePercent = -0.1f;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
AILevelDecreaseEvent::AILevelDecreaseEvent() :
	EventBase(true)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
AILevelDecreaseEvent::~AILevelDecreaseEvent()
{

}


//=============================================================================
// 初期化
//=============================================================================
void AILevelDecreaseEvent::Init()
{
	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void AILevelDecreaseEvent::Update()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	fieldEventHandler->AdjustLevelAI(DecreasePercent);

	// イベント終了、ゲーム続行
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void AILevelDecreaseEvent::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string AILevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("AIレベル減らすイベント");
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
