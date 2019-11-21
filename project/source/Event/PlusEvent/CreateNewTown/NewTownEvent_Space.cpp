//=============================================================================
//
// 新しい町(宇宙レベル)イベントクラス [NewTownEvent_Space.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_Space.h"
#include "../../EventActor/PlanetActor.h"
#include "../../../Viewer/GameScene/EventViewer/EventTelop.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../../Framework/Task/TaskManager.h"
#include "../../../Field/Camera/EventCamera.h"

enum State
{
	TelopExpanding,
	PlanetDebut,
	PlanetArrive,
};
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 落下速度
const float FallSpeed = 4.0f;
// 惑星モデルのスケール
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewTownEvent_Space::NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventState(TelopExpanding),
	EventOverFunc(EventOverFunc),
	camera(camera)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
NewTownEvent_Space::~NewTownEvent_Space()
{
	eventViewer = nullptr;
	NewPlanet = nullptr;
	SAFE_DELETE(PlanetModel);
}

//=============================================================================
// 初期化
//=============================================================================
void NewTownEvent_Space::Init()
{
	// 新しい惑星を作る予定座標を取得
	NewPlanet = fieldEventHandler->GetNewTownPosition();
	BuildPos = NewPlanet->GetPosition().ConvertToWorldPosition();

	// 惑星落下方向計算
	PlanetPos = BuildPos + D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	MoveDirection = BuildPos - PlanetPos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

	// 惑星メッシュ作成
	PlanetModel = new PlanetActor(PlanetPos, Scale, "Town-Space");

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::NewPlanet, [=]()
	{
		// 予定地にカメラを移動させる
		camera->Translation(PlanetPos, 30, [&]() {FallenStart(); });
	});

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void NewTownEvent_Space::Update()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	float Distance = 0.0f;

	switch (EventState)
	{
		// 惑星登場
	case PlanetDebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(PlanetPos - BuildPos));

		if (Distance > pow(4.0f, 2))
		{
			PlanetPos += MoveDirection * FallSpeed;
		}
		else
		{
			// 惑星到着エフェクト
			EventState = State::PlanetArrive;
		}

		camera->Translation(PlanetPos, 1, nullptr);

		break;

	default:
		break;
	}

}

//=============================================================================
// 描画
//=============================================================================
void NewTownEvent_Space::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	PlanetModel->SetPosition(PlanetPos);
	PlanetModel->Draw();
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
// 惑星落下開始
//=============================================================================
void NewTownEvent_Space::FallenStart(void)
{
	EventState = PlanetDebut;

	// 惑星落下エフェクト
	//GameParticleManager::Instance()->SetSingularityEffect(TownPos);
}

////=============================================================================
//// イベント終了処理
////=============================================================================
//void NewTownEvent_Space::EventOver(void)
//{
//	// イベント終了、ゲーム続行
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}