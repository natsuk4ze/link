//=============================================================================
//
// 新しい町イベントコントローラークラス [NewTownEventCtrl.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEventCtrl.h"
#include "NewTownEvent_City.h"
#include "NewTownEvent_World.h"
#include "NewTownEvent_Space.h"
#include "../../../Field/Camera/Plugin/FieldCameraTranslationPlugin.h"
#include "../../../Viewer/GameScene/EventViewer/EventViewer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewTownEventCtrl::NewTownEventCtrl(EventViewer *Ptr, int FieldLevel, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr)
{
	if (FieldLevel == Field::City)
	{
		NewTownEvent = new NewTownEvent_City(Ptr, [&]() {EventOver(); }, camera);
	}
	else if (FieldLevel == Field::World)
	{
		NewTownEvent = new NewTownEvent_World(Ptr, [&]() {EventOver(); }, camera);
	}
	else if (FieldLevel == Field::Space)
	{
		NewTownEvent = new NewTownEvent_Space(Ptr, [&]() {EventOver(); }, camera);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
NewTownEventCtrl::~NewTownEventCtrl()
{
	eventViewer = nullptr;
	SAFE_DELETE(NewTownEvent);
}

//=============================================================================
// 初期化
//=============================================================================
void NewTownEventCtrl::Init()
{
	NewTownEvent->Init();

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void NewTownEventCtrl::Update()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	NewTownEvent->Update();
}

//=============================================================================
// 描画
//=============================================================================
void NewTownEventCtrl::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	NewTownEvent->Draw();
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewTownEventCtrl::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// イベント終了処理
//=============================================================================
void NewTownEventCtrl::EventOver(void)
{
	// イベント終了、ゲーム続行
	FieldCameraTranslationPlugin::Instance()->Restore(30, nullptr);
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}