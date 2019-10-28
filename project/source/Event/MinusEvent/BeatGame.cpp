//=============================================================================
//
// 連打ゲームイベントクラス [BeatGame.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "BeatGame.h"
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Viewer/Framework/ViewerDrawer/countviewerdrawer.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Input/input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 連打ゲームの時間
const int InputTime = 3;
// 連打の回数
const int InputGoal = 20;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
TextViewer *BeatGame::Text = nullptr;
BaseViewerDrawer *BeatGame::point = nullptr;
CountViewerDrawer *BeatGame::fewNum = nullptr;
CountViewerDrawer *BeatGame::intNum = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
BeatGame::BeatGame(std::function<void(bool)> Callback) :
	RemainFrame(InputTime * 30),
	TelopOver(false),
	InputCount(0),
	Callback(Callback)
{
	Text->SetText("Cボタン連打！　残り 20 回");
}

//=============================================================================
// デストラクタ
//=============================================================================
BeatGame::~BeatGame()
{

}

//=============================================================================
// 初期化
//=============================================================================
void BeatGame::Init()
{
	// テキスト
	Text = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	Text->SetColor(SET_COLOR_NOT_COLORED);
	Text->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f + 120.0f));

	// 整数部
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

	// 小数部
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

	// 小数点
	point = new BaseViewerDrawer();
	point->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimerViewer/Point.png");
	point->MakeVertex();
	point->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	point->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	point->position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 2.0f, 0.0f);
	point->SetColor(SET_COLOR_NOT_COLORED);
}

//=============================================================================
// リリース
//=============================================================================
void BeatGame::Uninit()
{
	SAFE_DELETE(Text);
	SAFE_DELETE(point);
	SAFE_DELETE(fewNum);
	SAFE_DELETE(intNum);
}

//=============================================================================
// 更新
//=============================================================================
void BeatGame::Update()
{
	if (!UseFlag)
		return;

	if (!TelopOver)
	{
		return;
	}
	else
	{
		RemainFrame--;

		// カウント計算
		if (Keyboard::GetTrigger(DIK_C))
		{
			InputCount++;
		}

		char Message[64];
		sprintf(Message, "Cボタン連打！　残り %d 回", InputGoal - InputCount);
		Text->SetText(Message);

		if (InputCount >= 20)
		{
			// 成功
			Callback(true);
			UseFlag = false;
			return;
		}

		if (RemainFrame <= 0)
		{
			// 失敗
			Callback(false);
			UseFlag = false;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void BeatGame::Draw()
{
	if (!UseFlag)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テキスト
	Text->Draw();

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAREF, 0);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// 小数点
	point->Draw();
	point->SetVertex();

	float RemainTime = RemainFrame / 30.0f;

	// 整数部
	intNum->DrawCounter(intNum->baseNumber, (int)RemainTime, intNum->placeMax,
		intNum->intervalNumberScr, intNum->intervalNumberTex);

	// 小数部
	fewNum->DrawCounter(fewNum->baseNumber, (int)((RemainTime - (int)RemainTime)*pow(fewNum->baseNumber, fewNum->placeMax)), fewNum->placeMax,
		fewNum->intervalNumberScr, fewNum->intervalNumberTex);

	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string BeatGame::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
void BeatGame::CountdownStart(void)
{
	TelopOver = true;
}