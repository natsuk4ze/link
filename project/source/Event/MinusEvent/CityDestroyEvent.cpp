//=============================================================================
//
// 町消滅イベントクラス [CityDestroyEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "CityDestroyEvent.h"
#include "BeatGame.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Effect/GameParticleManager.h"
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
// 隕石の半径
const float MeteoriteRadius = 3.0f;
const float MeteoriteDistance = 200.0f;
const float FallSpeed = 4.0f;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
#if _DEBUG
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
D3DMATERIAL9 CityDestroyEvent::Material =
{
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// Diffuse color RGBA
	D3DXCOLOR(1.0f, 0.65f, 0.0f, 1.0f),	// Ambient color RGB
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Specular 'shininess'
	D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),	// Emissive color RGB
	0.0f,								// Sharpness if specular highlight 
};
#endif

//=============================================================================
// コンストラクタ
//=============================================================================
CityDestroyEvent::CityDestroyEvent(EventViewer* eventViewer) :
	EventState(State::TelopExpanding)
{
	// 連打ゲームインスタンス
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// 破壊する町の予定地を取得
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {MeteorFallStart(); });
	});

	// 隕石落下方向計算
	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

#if _DEBUG
	// 球体メッシュを作成する
	if (SphereMesh == nullptr)
	{
		LPDIRECT3DDEVICE9 Device = GetDevice();
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
	}
#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
CityDestroyEvent::~CityDestroyEvent()
{
	SAFE_DELETE(beatGame);
}

//=============================================================================
// 更新
//=============================================================================
void CityDestroyEvent::Update()
{
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
		GameParticleManager::Instance()->SetMissileHitEffect(MeteoritePos);
		// 30フレームの遅延を設置
		TaskManager::Instance()->CreateDelayedTask(30, [&]()
		{
			Camera::TranslationPlugin::Instance()->Restore(60, [&]() { EventOver(); });
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
			// 隕石落下エフェクト
			GameParticleManager::Instance()->SetMeteorExplosionEffect(TownPos);
			// 30フレームの遅延を設置
			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				Camera::TranslationPlugin::Instance()->Restore(60, [&]() { EventOver(); });
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
	LPDIRECT3DDEVICE9 Device = GetDevice();

#if _DEBUG
	if (EventState != State::EffectHappend)
	{
		D3DXMATRIX WorldMatrix, TransMatrix;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&WorldMatrix);

		// 移動を反映
		D3DXMatrixTranslation(&TransMatrix, MeteoritePos.x, MeteoritePos.y, MeteoritePos.z);
		D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

		// ワールドマトリックスの設定
		Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

		// マテリアルの設定
		Device->SetMaterial(&Material);

		// 球体描画
		SphereMesh->DrawSubset(0);
	}
#endif

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
