//=============================================================================
//
// 新しい町(国レベル)イベントクラス [NewTownEvent_World.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_World.h"
#include "../../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/WorldParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../Field/Camera/EventCamera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewTownEvent_World::NewTownEvent_World(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera* camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc),
	camera(camera)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
NewTownEvent_World::~NewTownEvent_World()
{
	eventViewer = nullptr;
	NewTown = nullptr;
}

//=============================================================================
// 初期化
//=============================================================================
void NewTownEvent_World::Init()
{
	// 新しい国を作る予定地を取得
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::Atlantis, [=]()
	{
		// 予定地にカメラを移動させる
		camera->Translation(TownPos, 30, [&]() {CreateNewTown(); });
	});

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void NewTownEvent_World::Update()
{

}

//=============================================================================
// 描画
//=============================================================================
void NewTownEvent_World::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewTownEvent_World::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// 新しい町を作る
//=============================================================================
void NewTownEvent_World::CreateNewTown(void)
{
	D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();
	D3DXVECTOR3 Amplitude = D3DXVECTOR3(5.0f, 3.0f, 5.0f);

	CameraShakePlugin::Instance()->Set(Amplitude, 300);
	fieldEventHandler->CreateNewTown(NewTown);
	WorldParticleManager::Instance()->SetAtlantisEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(180, [&]() {EventOverFunc(); });
}

////=============================================================================
//// イベント終了処理
////=============================================================================
//void NewTownEvent_World::EventOver(void)
//{
//	// イベント終了、ゲーム続行
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}