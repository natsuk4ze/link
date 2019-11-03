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

enum State
{
	TelopExpanding,
	UFODebut,
	BeatGameStart,
	BeatGameSuccess,
	BeatGameFail,
	EffectHappend,
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

	// 隕石落下方向計算
	UFOPos = TownPos + Vector3::Up * 40.0f;

	// 隕石メッシュ作成
	UFO = new EventActor(UFOPos, Scale, "UFO");

	// テロップ設置
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
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
	case UFODebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(UFOPos - TownPos));

		if (Distance > pow(25.0f, 2))
		{
			UFOPos += Vector3::Down * FallSpeed;
		}
		else
		{
			CountdownStart();
			EventState = State::BeatGameStart;
		}
		break;

	case BeatGameStart:

		/*float RadiusX = 1.0f;
		float RadiusY = 2.0f;
		float RadiusZ = 3.0f;
		float RateX = 3.0f;
		float RateY = 4.0f;
		float RateZ = 5.0f;

		D3DXVECTOR3 hover = D3DXVECTOR3
		{
				RadiusX * sinf(RateX * (float)FrameCount),
				RadiusY * sinf(RateY * (float)FrameCount),
				RadiusZ * sinf(RateZ * (float)FrameCount)
		};

		UFOPos += hover;*/

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

		// 30フレームの遅延を設置
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			Camera::TranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
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
		UFO->SetPosition(UFOPos);
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


