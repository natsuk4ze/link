//=============================================================================
//
// 新しい町(都市レベル)イベントクラス [NewTownEvent_City.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_City.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/CityParticleManager.h"
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
NewTownEvent_City::NewTownEvent_City(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventOverFunc(EventOverFunc),
	camera(camera)
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
	TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::Singularity, [&]()
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
	CityParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(90, [&]() 
	{
		camera->Return(15, EventOverFunc);
	});
}
