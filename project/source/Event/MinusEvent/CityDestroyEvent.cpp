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
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Viewer/Framework/ViewerDrawer/countviewerdrawer.h"

#include "../../../Framework/Camera/CameraTranslationPlugin.h"

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
	//CountOver(false),
	//TelopOver(false),
	//RemainFrame(EscapeTime * 30)
{
#if 0
	//整数部
	intNum = new CountViewerDrawer();
	intNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	intNum->MakeVertex();
	intNum->size = D3DXVECTOR3(60.0f, 60.0f, 0.0f);
	intNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	intNum->position = D3DXVECTOR3(SCREEN_WIDTH / 2 - 140.0f, SCREEN_HEIGHT / 10 * 2.0f + 20.0f, 0.0f);
	intNum->SetColor(SET_COLOR_NOT_COLORED);
	intNum->intervalNumberScr = 80.0f;
	intNum->intervalNumberTex = 0.1f;
	intNum->placeMax = 2;
	intNum->baseNumber = 10;

	//小数部
	fewNum = new CountViewerDrawer();
	fewNum->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Number.png");
	fewNum->MakeVertex();
	fewNum->size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
	fewNum->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fewNum->position = D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, SCREEN_HEIGHT / 10 * 2.0f + 30.0f, 0.0f);
	fewNum->SetColor(SET_COLOR_NOT_COLORED);
	fewNum->intervalNumberScr = 40.0f;
	fewNum->intervalNumberTex = 0.1f;
	fewNum->placeMax = 2;
	fewNum->baseNumber = 10;

	//小数点
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->MakeVertex();
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 2.0f, 0.0f);
	point->SetColor(SET_COLOR_NOT_COLORED);

#endif

	// 連打ゲームインスタンス
	beatGame = new BeatGame(eventViewer, [&](bool EventAvoid) { UseMissile(EventAvoid); });

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
	SAFE_DELETE(point);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(intNum);
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
				// 隕石爆発エフェクト
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
				// 町消滅エフェクト
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				// 町消滅処理
				fieldEventHandler->DestroyTown(Target);

				this->UseFlag = false;
			}
		}
	}

#if 0
	if (!CountOver)
	{
		RemainFrame--;
		if (RemainFrame <= 0)
		{
			CountOver = true;
			fieldEventHandler->PauseGame();
			Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]()
			{
				// 地球防衛軍使用
				if (fieldEventHandler->TryUsingEDF())
				{
					// ミサイル使用
					UseMissile(true);
				}
				else
				{
					UseMissile(false);
				}
			});
		}
	}
	else
	{
		if (EventAvoid)
		{
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - MissilePos));

			if (Distance > pow(3.0f, 2))
			{
				MissilePos += MoveDirection * FallSpeed;
				MeteoritePos += -MoveDirection * FallSpeed;
				Camera::TranslationPlugin::Instance()->Move(MissilePos, 1, nullptr);
			}
			else
			{
				// 隕石爆発エフェクト
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
		else
		{
			float Distance = D3DXVec3LengthSq(&D3DXVECTOR3(MeteoritePos - TownPos));

			if (Distance > pow(3.0f, 2))
			{
				MeteoritePos += MoveDirection * FallSpeed;
			}
			else
			{
				// 町消滅エフェクト
				Camera::TranslationPlugin::Instance()->Restore(60, nullptr);
				this->UseFlag = false;
			}
		}
}
#endif

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

#if 0
	if (!CountOver)
	{
		Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		Device->SetRenderState(D3DRS_ALPHAREF, 0);
		Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		//小数点
		point->Draw();
		point->SetVertex();

		float RemainTime = RemainFrame / 30.0f;

		//整数部
		intNum->DrawCounter(intNum->baseNumber, (int)RemainTime, intNum->placeMax,
			intNum->intervalNumberScr, intNum->intervalNumberTex);

		//小数部
		fewNum->DrawCounter(fewNum->baseNumber, (int)((RemainTime - (int)RemainTime)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
			fewNum->intervalNumberScr, fewNum->intervalNumberTex);

		Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
	else
	{
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
#endif
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string CityDestroyEvent::GetEventMessage(int FieldLevel)
{
#if 0
	vector<string> MessageContainer;

	if (FieldLevel == Field::Model::City)
	{
		MessageContainer.push_back("この町は焚き火にしよう");
	}
	else if (FieldLevel == Field::Model::World)
	{

	}
	else if (FieldLevel == Field::Model::Space)
	{

	}

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "イベントメッセージがありません";
		return ErrMsg;
	}
#endif
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
// ミサイル発射
//=============================================================================
void CityDestroyEvent::UseMissile(bool Flag)
{
	BeatGameOver = true;

	if (!Flag)
	{
		EventAvoid = false;
		return;
	}
	else
	{
		EventAvoid = true;
		MoveDirection = D3DXVECTOR3(MeteoritePos - MissilePos);
		D3DXVec3Normalize(&MoveDirection, &MoveDirection);
	}
}
