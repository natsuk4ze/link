//=============================================================================
//
// 町消滅イベントクラス [CityDestroyEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
#include "BeatGame.h"
#include "../EventActor/EventActorBase.h"
#include "../../Field/Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Framework/Task/TaskManager.h"

enum State
{
	TelopExpanding,
	MeteorDebut,
	BeatGameStart,
	BeatGameSuccess,
	BeatGameFail,
	EffectHappend,
};
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 隕石の初期位置と予定地の距離
const float MeteoriteDistance = 200.0f;
// 落下速度
const float FallSpeed = 4.0f;
// 隕石モデルのスケール
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(Meteor);
	SAFE_DELETE(beatGame);
	eventViewer = nullptr;
}

//=============================================================================
// 初期化
//=============================================================================
void CityDestroyEvent::Init()
{
	// 連打ゲームインスタンス
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// 破壊する町の予定地を取得
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 隕石落下方向計算
	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

	// 隕石メッシュ作成
	Meteor = new EventActorBase(MeteoritePos, Scale, "Meteor");

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::Meteorite, [&]()
	{
		CameraTranslationPlugin::Instance()->Move(TownPos, 30, [&]() {MeteorFallStart(); });
	});

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void CityDestroyEvent::Update()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	float Distance = 0.0f;

	switch (EventState)
	{
		// 隕石登場
	case MeteorDebut:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

		if (Distance > pow(20.0f, 2))
		{
			MeteoritePos += MoveDirection * FallSpeed;
		}
		else
		{
			CountdownStart();
			EventState = State::BeatGameStart;
		}
		break;

	case BeatGameStart:

		// 連打ゲームの更新
		beatGame->Update();
		break;

		// 隕石撃破
	case BeatGameSuccess:

		// 隕石撃破エフェクト
		GameParticleManager::Instance()->SetMeteorExplosionEffect(MeteoritePos);
		// 30フレームの遅延を設置
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			CameraTranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

		// 隕石落下
	case BeatGameFail:

		Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

		if (Distance > pow(3.0f, 2))
		{
			MeteoritePos += MoveDirection * FallSpeed;
		}
		else
		{
			// 町消滅エフェクト
			GameParticleManager::Instance()->SetTownExplosionEffect(TownPos);
			// 30フレームの遅延を設置
			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				CameraTranslationPlugin::Instance()->Restore(30, [&]() { EventOver(); });
			});
			// 町消滅処理
			fieldEventHandler->DestroyTown(Target);
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
void CityDestroyEvent::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	if (EventState != State::EffectHappend)
	{
		Meteor->SetPosition(MeteoritePos);
		Meteor->Draw();
	}

	beatGame->Draw();
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string CityDestroyEvent::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// イベント終了処理
//=============================================================================
void CityDestroyEvent::EventOver(void)
{
	// イベント終了、ゲーム続行
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}

//=============================================================================
// テロップ再生終了、隕石落下開始
//=============================================================================
void CityDestroyEvent::MeteorFallStart(void)
{
	EventState = State::MeteorDebut;
}

//=============================================================================
// 連打ゲームのカウントダウン開始
//=============================================================================
void CityDestroyEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
}

//=============================================================================
// 連打ゲームの結果による処理
//=============================================================================
void CityDestroyEvent::ReceiveBeatResult(bool IsSuccess)
{
	if (IsSuccess)
	{
		// 成功、隕石撃破
		EventState = State::BeatGameSuccess;
	}
	else
	{
		// 失敗、隕石落下
		EventState = State::BeatGameFail;
	}
}
