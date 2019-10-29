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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 隕石の半径
const float MeteoriteRadius = 3.0f;
const float MeteoriteDistance = 200.0f;
const float FallSpeed = 4.0f;
// 隕石が来るまでの時間
const int EscapeTime = 10;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
#if _DEBUG
LPD3DXMESH CityDestroyEvent::SphereMesh = nullptr;
LPD3DXMESH CityDestroyEvent::MissileMesh = nullptr;
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
	EventAvoid(false),
	BeatGameOver(false)
{
	// 連打ゲームインスタンス
	beatGame = new BeatGame([&](bool IsSuccess) { ReceiveBeatResult(IsSuccess); });

	// 破壊する町の予定地を取得
	Target = fieldEventHandler->GetDestroyTarget();
	TownPos = Target->GetPosition().ConvertToWorldPosition();
	MissilePos = TownPos;

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(NegativeEvent01, [&]()
	{
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]()
		{
			CountdownStart();
		});
	});

	MeteoritePos = TownPos + D3DXVECTOR3(MeteoriteDistance, MeteoriteDistance, 0.0f);
	MoveDirection = TownPos - MeteoritePos;
	D3DXVec3Normalize(&MoveDirection, &MoveDirection);

#if _DEBUG
	// 球体メッシュを作成する
	if (SphereMesh == nullptr)
	{
		LPDIRECT3DDEVICE9 Device = GetDevice();
		D3DXCreateSphere(Device, MeteoriteRadius, 16, 16, &SphereMesh, NULL);
		D3DXCreateSphere(Device, 1.0f, 16, 16, &MissileMesh, NULL);
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
	if (!BeatGameOver)
	{
		beatGame->Update();
	}
	else
	{
		if (EventAvoid)
		{
			// =================
			// ミサイル発射
			// =================
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - MissilePos));

			if (Distance > pow(3.0f, 2))
			{
				MissilePos += MoveDirection * FallSpeed;
				MeteoritePos += -MoveDirection * FallSpeed;
				Camera::TranslationPlugin::Instance()->Move(MissilePos, 1, nullptr);
			}
			else
			{
				// ミサイル命中エフェクト
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
		else
		{
			// =================
			// 隕石落下
			// =================
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

			if (Distance > pow(3.0f, 2))
			{
				MeteoritePos += MoveDirection * FallSpeed;
			}
			else
			{
				// 隕石落下エフェクト
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				// 町消滅処理
				fieldEventHandler->DestroyTown(Target);
				this->UseFlag = false;
			}
		}
	}

	if (!UseFlag)
	{
		// イベント終了、ゲーム続行
		fieldEventHandler->ResumeGame();
	}
}

//=============================================================================
// 描画
//=============================================================================
void CityDestroyEvent::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	beatGame->Draw();

#if _DEBUG
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

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&WorldMatrix);

	// 移動を反映
	D3DXMatrixTranslation(&TransMatrix, MissilePos.x, MissilePos.y, MissilePos.z);
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TransMatrix);

	// ワールドマトリックスの設定
	Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

	// ミサイル描画
	MissileMesh->DrawSubset(0);
#endif
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
// 隕石が来るまでのカウントダウン
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
	BeatGameOver = true;

	if (IsSuccess)
	{
		// 成功、ミサイル発射
		EventAvoid = true;
		MoveDirection = D3DXVECTOR3(MeteoritePos - MissilePos);
		D3DXVec3Normalize(&MoveDirection, &MoveDirection);
	}
	else
	{
		// 失敗、隕石落下
		EventAvoid = false;
	}
}
