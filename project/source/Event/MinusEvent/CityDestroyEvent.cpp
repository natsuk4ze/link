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
#include "../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../Field/Camera/EventCamera.h"
#include "../../Viewer/GameScene/GuideViewer/GuideActor.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"
#include "../../Sound/PlayBGM.h"
#include "../../Booth/BoothController.h"

enum State
{
	TelopExpanding,
	MeteorDebut,
	CameraMoveWait,
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
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer, BeatGameViewer* beatViewer, EventCamera* camera) :
	EventBase(true),
	EventState(State::TelopExpanding),
	eventViewer(eventViewer),
	camera(camera),
	beatViewer(beatViewer),
	success(false)
{
	PlayBGM::Instance()->Pause();
}

//=============================================================================
// デストラクタ
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(Meteor);
	SAFE_DELETE(beatGame);
	SAFE_DELETE(guideActor);
	eventViewer = nullptr;
}

//=============================================================================
// 初期化
//=============================================================================
void CityDestroyEvent::Init()
{
	//カメラをイベントカメラに切り替え
	camera->Init();

	// 連打ゲームインスタンス
	auto onFinishBeat = std::bind(&CityDestroyEvent::OnFinisheBeat, this, std::placeholders::_1);
	beatGame = new BeatGame(BeatGame::CityDestroyEvent, beatViewer, [&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); }, onFinishBeat);

	// 破壊する町の予定地を取得
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// 隕石落下方向計算
	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

	// 隕石メッシュ作成
	Meteor = new EventActorBase(MeteoritePos, Scale, "Meteor");

	//ガイドキャラ作成
	guideActor = new GuideActor();
	guideActor->SetActive(false);
	guideActor->SetScale(Vector3::One * 0.05f);

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::Meteorite, [&]()
	{
		PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::DestroyEvent, 0.1f, 30);
		camera->Translation(TownPos, 30, [&]() {MeteorFallStart(); });
	});

	//ブースのLEDを点滅させる
	BoothController::Instance()->BlinkLED(false);

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
	D3DXVECTOR3 diff = Vector3::Zero;

	switch (EventState)
	{
		// 隕石登場
	case MeteorDebut:

		diff = TownPos - MeteoritePos;
		Distance = D3DXVec3LengthSq(&diff);

		if (Distance > pow(40.0f, 2))
		{
			MeteoritePos += MoveDirection * FallSpeed;
		}
		else
		{
			EventState = CameraMoveWait;

			//ガイドキャラをアクティベイトして移動
			guideActor->SetActive(true);
			
			D3DXVECTOR3 guidePos = Vector3::Normalize(diff) * 7.5f + MeteoritePos;
			guideActor->SetPosition(TownPos);
			guideActor->Move(guidePos, 60);

			guideActor->LookAt(MeteoritePos);

			guideActor->ChangeAnim(GuideActor::AnimState::FightingIdle, true);

			//カメラの移動
			D3DXVECTOR3 nextCameraPos = Vector3::Normalize(diff) * 25.0f + MeteoritePos + Vector3::Back * 10.0f;
			camera->Move(nextCameraPos, 30, 35.0f, [this]
			{
				CountdownStart();
			});
		}
		break;

	case BeatGameStart:

		// 連打ゲームの更新
		beatGame->Update();
		break;

		// 隕石撃破
	case BeatGameSuccess:

		PlayBGM::Instance()->FadeOut();
		// 隕石撃破エフェクト
		GameParticleManager::Instance()->SetMeteorExplosionEffect(MeteoritePos);
		// 30フレームの遅延を設置
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			guideActor->SetActive(false);
			camera->Return(30, [&]() { EventOver(); });
		});
		EventState = EffectHappend;
		break;

		// 隕石落下
	case BeatGameFail:

		PlayBGM::Instance()->FadeOut();
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
				camera->Return(30, [&]() { EventOver(); });
			});
			// 町消滅処理
			fieldEventHandler->DestroyTown(Target);
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

	if (guideActor->IsActive())
		guideActor->Draw();

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
	camera->Restore();
	fieldEventHandler->ResumeGame();
	UseFlag = false;

	// イベントの可否によって再生を変更
	if (success)
	{
		GuideViewer::Instance()->SetData("いん石の破壊に成功",
			GuideActor::AnimState::Clapping,
			SoundConfig::MeteorBreakSuccess);
	}
	else
	{
		GuideViewer::Instance()->SetData("いん石の破壊に失敗",
			GuideActor::AnimState::Defeat,
			SoundConfig::MeteorBreakFailed);
	}
	PlayBGM::Instance()->ResumePrev();
}

//=============================================================================
// テロップ再生終了、隕石落下開始
//=============================================================================
void CityDestroyEvent::MeteorFallStart(void)
{
	EventState = State::MeteorDebut;
	camera->SetTargetObject(Meteor);
}

//=============================================================================
// 連打ゲームのカウントダウン開始
//=============================================================================
void CityDestroyEvent::CountdownStart(void)
{
	beatGame->CountdownStart();
	EventState = State::BeatGameStart;

	//ガイドアクターのアニメーション
	guideActor->ChangeAnim(GuideActor::AnimState::FightingIdle, true);

	TaskManager::Instance()->CreateDelayedTask(90, [&]()
	{
		guideActor->StartPunsh();
	});
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
		success = true;

		SE::Play(SoundConfig::SEID::Bom, 1.0f);
	}
	else
	{
		// 失敗、隕石落下
		EventState = State::BeatGameFail;
		success = false;
		
		D3DXVECTOR3 cameraPos = camera->GetPosition() + Vector3::Up * 30.0f;
		camera->Move(cameraPos, 10, 100.0f, []() {
			SE::Play(SoundConfig::SEID::Bom, 1.0f);
		});

		guideActor->SetActive(false);
	}
}

//=============================================================================
// 連打ゲームの結果によるアニメーション遷移
//=============================================================================
void CityDestroyEvent::OnFinisheBeat(bool result)
{
	guideActor->EndPunch(result);
}
