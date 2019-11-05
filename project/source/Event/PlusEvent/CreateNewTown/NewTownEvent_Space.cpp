//=============================================================================
//
// 新しい町(宇宙レベル)イベントクラス [NewTownEvent_Space.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_Space.h"
#include "../../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewTownEvent_Space::NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
NewTownEvent_Space::~NewTownEvent_Space()
{
	eventViewer = nullptr;
	NewTown = nullptr;
}

//=============================================================================
// 初期化
//=============================================================================
void NewTownEvent_Space::Init()
{
	// 新しい町を作る予定地を取得
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(PositiveEvent01, [=]()
	{
		// 予定地にカメラを移動させる
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {CreateNewTown(); });
	});

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void NewTownEvent_Space::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void NewTownEvent_Space::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewTownEvent_Space::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// 新しい町を作る
//=============================================================================
void NewTownEvent_Space::CreateNewTown(void)
{
	D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	fieldEventHandler->CreateNewTown(NewTown);
	GameParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() {EventOverFunc(); });
}

////=============================================================================
//// イベント終了処理
////=============================================================================
//void NewTownEvent_Space::EventOver(void)
//{
//	// イベント終了、ゲーム続行
//	Camera::TranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}