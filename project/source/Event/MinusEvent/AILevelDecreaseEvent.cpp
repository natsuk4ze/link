//=============================================================================
//
// AIレベル減少イベントクラス [AILevelDecreaseEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "AILevelDecreaseEvent.h"
#include "BeatGame.h"
#include "../EventActor.h"
#include "../../Field/Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Framework/Task/TaskManager.h"

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
AILevelDecreaseEvent::AILevelDecreaseEvent(EventViewer* eventViewer) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
AILevelDecreaseEvent::~AILevelDecreaseEvent()
{
	SAFE_DELETE(beatGame);
	SAFE_DELETE(UFO);
	eventViewer = nullptr;
}


//=============================================================================
// 初期化
//=============================================================================
void AILevelDecreaseEvent::Init()
{
	// 連打ゲームインスタンス
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// 目標町の予定地を取得
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 初期座標設定
	UFOPos = TownPos + Vector3::Up * DefaultHeight;

	// UFOメッシュ作成
	UFO = new EventActor(UFOPos, Scale, "UFO");

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {UFODebutStart(); });
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
		break;

		// UFO撃墜
	case BeatGameSuccess:

		// UFO撃墜エフェクト
		GameParticleManager::Instance()->SetMeteorExplosionEffect(UFOPos);
		// 30フレームの遅延を設置
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			Camera::TranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
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
			Camera::TranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
			EventState = EffectHappend;
		}
		break;

	default:
		break;
	}
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
	EventState = UFODebut;
}

//=============================================================================
// イベント終了処理
//=============================================================================
void AILevelDecreaseEvent::EventOver(void)
{
	// イベント終了、ゲーム続行
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
	}
}


