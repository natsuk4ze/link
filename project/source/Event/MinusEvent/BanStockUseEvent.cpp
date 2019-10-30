//=============================================================================
//
// ストック使用不可イベントクラス [BanStockUseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "BanStockUseEvent.h"
#include "../MinusEvent/BeatGame.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// デフォルトの効果時間
const int DefaultDebuffFrame = 300;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
BanStockUseEvent::BanStockUseEvent(EventViewer* eventViewer) :
	RemainTime(DefaultDebuffFrame)
{
	// 連打ゲームインスタンス
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(NegativeEvent01, nullptr);

	// 怒り顔エフェクト設置
	GameParticleManager::Instance()->SetAngryFaceEffect();

	TaskManager::Instance()->CreateDelayedTask(90, [&]() {CountdownStart(); });
}

//=============================================================================
// デストラクタ
//=============================================================================
BanStockUseEvent::~BanStockUseEvent()
{
	SAFE_DELETE(beatGame);
}

//=============================================================================
// 更新
//=============================================================================
void BanStockUseEvent::Update()
{
	RemainTime--;
	if (RemainTime <= 0)
	{
		// 封印解除
		fieldEventHandler->SealUsingItem(false);
		UseFlag = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void BanStockUseEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string BanStockUseEvent::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// イベント終了処理
//=============================================================================
void BanStockUseEvent::EventOver(void)
{
	// イベント終了、ゲーム続行
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// 連打ゲームのカウントダウン開始
//=============================================================================
void BanStockUseEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
}

//=============================================================================
// 連打ゲームの結果による処理
//=============================================================================
void BanStockUseEvent::ReceiveBeatResult(bool IsSuccess)
{
	if (IsSuccess)
	{
		// 成功
		EventOver();
	}
	else
	{
		// 失敗、ストック使用封印
		fieldEventHandler->SealUsingItem(true);
	}
}

