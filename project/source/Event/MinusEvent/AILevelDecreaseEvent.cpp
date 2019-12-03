//=============================================================================
//
// AIレベル減少イベントクラス [AILevelDecreaseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "AILevelDecreaseEvent.h"
#include "BeatGame.h"
#include "../EventActor/UFOActor.h"
#include "../../Field/Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Field/Camera/EventCamera.h"
#include "../../Viewer/GameScene/Controller/BeatGameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideActor.h"
#include "../../../Framework/Tween/Tween.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// UFOの降下速度
const float FallSpeed = 0.2f;
// AIレベル減らすの効果値
const float DecreasePercent = -0.1f;
// UFOモデルのスケール
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
// デフォルトの高さ
const float DefaultHeight = 50.0f;

enum State
{
	TelopExpanding,
	UFODebut,
	BeatGameStart,
	BeatGameSuccess,
	BeatGameFail,
	EffectHappend,
	UFOExit,
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
AILevelDecreaseEvent::AILevelDecreaseEvent(EventViewer* eventViewer, EventCamera *camera, BeatGameViewer *beatViewer) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer),
	camera(camera),
	beatViewer(beatViewer)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
AILevelDecreaseEvent::~AILevelDecreaseEvent()
{
	SAFE_DELETE(beatGame);
	SAFE_DELETE(UFO);
	SAFE_DELETE(guideActor);
	eventViewer = nullptr;
}


//=============================================================================
// 初期化
//=============================================================================
void AILevelDecreaseEvent::Init()
{
	//カメラをイベントカメラに切り替え
	camera->Init();

	// 連打ゲームインスタンス
	beatGame = new BeatGame(BeatGame::AILevelDecrease, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// 目標町の予定地を取得
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 初期座標設定
	UFOPos = TownPos + Vector3::Up * DefaultHeight;

	// UFOメッシュ作成
	UFO = new UFOActor(UFOPos, Scale, "UFO");

	//ガイド作成
	guideActor = new GuideActor();
	guideActor->SetActive(false);
	guideActor->SetScale(Vector3::One * 0.05f);

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::Alien, [&]()
	{
		camera->Translation(TownPos, 30, [&]() {UFODebutStart(); });
	});

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

	float Distance = 0.0f;

	switch (EventState)
	{
		// UFO登場
	case UFODebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(UFOPos - TownPos));

		if (Distance > pow(25.0f, 2))
		{
			UFOPos += Vector3::Down * FallSpeed;
			UFO->SetPosition(UFOPos);
		}
		else
		{
			CountdownStart();
			EventState = State::BeatGameStart;
		}
		break;

	case BeatGameStart:

		UFO->Update();

		// 連打ゲームの更新
		beatGame->Update();

		//ガイドをUFOに向かせる
		guideActor->LookAt(UFOPos);

		break;

		// UFO撃墜
	case BeatGameSuccess:

		// UFO撃墜エフェクト
		GameParticleManager::Instance()->SetMeteorExplosionEffect(UFOPos);
		// 30フレームの遅延を設置
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			camera->Return(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

		// AIレベル減らす
	case BeatGameFail:

		UFO->Update();

		// エフェクト
		GameParticleManager::Instance()->SetDarknessEffect(TownPos);
		TaskManager::Instance()->CreateDelayedTask(90, [&]()
		{
			EventState = UFOExit;
		});
		break;

		// UFO退場
	case UFOExit:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(UFOPos - TownPos));

		if (Distance < pow(DefaultHeight, 2))
		{
			UFOPos += Vector3::Up * FallSpeed;
			UFO->SetPosition(UFOPos);
		}
		else
		{
			camera->Return(30, [&]() { EventOver(); });
			EventState = EffectHappend;
		}
		break;

	default:
		break;
	}

	if (guideActor->IsActive())
		guideActor->Update();
}

//=============================================================================
// 描画
//=============================================================================
void AILevelDecreaseEvent::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	if (EventState != State::EffectHappend)
	{
		UFO->Draw();
	}

	if (guideActor->IsActive())
		guideActor->Draw();

	beatGame->Draw();
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string AILevelDecreaseEvent::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// UFOが登場開始
//=============================================================================
void AILevelDecreaseEvent::UFODebutStart(void)
{
	//カメラの位置を切り替え
	D3DXVECTOR3 cameraPos = TownPos + D3DXVECTOR3(15.0f, 15.0f, -15.0f);
	camera->Move(cameraPos, 10, 10.0f);
	camera->SetTargetObject(UFO);
	EventState = UFODebut;
}

//=============================================================================
// イベント終了処理
//=============================================================================
void AILevelDecreaseEvent::EventOver(void)
{
	// イベント終了、ゲーム続行
	camera->Restore();
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// 連打ゲームのカウントダウン開始
//=============================================================================
void AILevelDecreaseEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
	UFO->SetHoverMotion(true);

	//カメラの追従を切る
	camera->SetTargetObject(nullptr);
	
	//ガイドキャラ出撃
	D3DXVECTOR3 diff = Vector3::Normalize(camera->GetPosition() - UFOPos);
	D3DXVECTOR3 guidePos = UFOPos + diff * 5.0f + Vector3::Down * 2.0f;

	Tween::Move(*guideActor, TownPos, guidePos, 15, EaseType::OutCubic);

	guideActor->SetActive(true);
}

//=============================================================================
// 連打ゲームの結果による処理
//=============================================================================
void AILevelDecreaseEvent::ReceiveBeatResult(bool IsSuccess)
{
	if (IsSuccess)
	{
		// 成功
		EventState = BeatGameSuccess;
	}
	else
	{
		// 失敗
		fieldEventHandler->AdjustLevelAI(DecreasePercent);
		EventState = BeatGameFail;

		//ガイドキャラに失敗モーションをさせる
		guideActor->ChangeAnim(GuideActor::AnimState::Defeat);
	}
}


