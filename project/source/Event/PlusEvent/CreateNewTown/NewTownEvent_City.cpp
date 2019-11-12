//=============================================================================
//
// 新しい町(都市レベル)イベントクラス [NewTownEvent_City.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_City.h"
#include "../../../Field/Camera/Plugin/FieldCameraTranslationPlugin.h"
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
NewTownEvent_City::NewTownEvent_City(EventViewer *Ptr, std::function<void(void)> EventOverFunc) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
NewTownEvent_City::~NewTownEvent_City()
{
	eventViewer = nullptr;
	NewTown = nullptr;
}

//=============================================================================
// 初期化
//=============================================================================
void NewTownEvent_City::Init()
{
	// 新しい町を作る予定地を取得
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::NewPlanet, [=]()
	{
		// 予定地にカメラを移動させる
		FieldCameraTranslationPlugin::Instance()->Move(TownPos, 30, [&]() {CreateNewTown(); });
	});

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void NewTownEvent_City::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void NewTownEvent_City::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewTownEvent_City::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// 新しい町を作る
//=============================================================================
void NewTownEvent_City::CreateNewTown(void)
{
	D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	fieldEventHandler->CreateNewTown(NewTown);
	GameParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() {EventOverFunc(); });
}

////=============================================================================
//// イベント終了処理
////=============================================================================
//void NewTownEvent_City::EventOver(void)
//{
//	// イベント終了、ゲーム続行
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}