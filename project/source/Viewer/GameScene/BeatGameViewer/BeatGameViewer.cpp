//=============================================================================
//
// 連打ゲームビュアー管理処理 [BeatGameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "BeatTitleViewer.h"
#include "BeatGaugeViewer.h"
#include "BeatTimerViewer.h"
#include "BeatStarterViewer.h"
#include "BeatResultViewer.h"
#include "BeatGameViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BeatGameViewer::BeatGameViewer()
{
	beatGameViewer.push_back(titleViewer = new BeatTitleViewer);
	beatGameViewer.push_back(gaugeViewer = new BeatGaugeViewer);
	beatGameViewer.push_back(timerViewer = new BeatTimerViewer);
	beatGameViewer.push_back(starterViewer = new BeatStarterViewer);
	beatGameViewer.push_back(resultViewer = new BeatResultViewer);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatGameViewer::~BeatGameViewer()
{
	//メモリを解放
	for (unsigned int i = 0; i < beatGameViewer.size(); i++)
	{
		SAFE_DELETE(beatGameViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	beatGameViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatGameViewer::Update()
{
	for (unsigned int i = 0; i < beatGameViewer.size(); i++)
	{
		beatGameViewer[i]->Update();
	}

#ifdef _DEBUG

	SetGameTitle(titleViewer->CalmAI);
	SetRemainTime(0);

	if (Keyboard::GetTrigger(DIK_R))
	{
		SetReady();
	}

	if (Keyboard::GetTrigger(DIK_G))
	{
		SetGo();
	}

	if (Keyboard::GetTrigger(DIK_3))
	{
		SetResult(resultViewer->Failed, nullptr);
	}

	if (Keyboard::GetTrigger(DIK_4))
	{
		SetResult(resultViewer->Success, nullptr);
	}

#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void BeatGameViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < beatGameViewer.size(); i++)
	{
		beatGameViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// 連打ゲームのタイトルを設置する処理
//=============================================================================
void BeatGameViewer::SetGameTitle(BeatTitleViewer::TitleID id)
{
	titleViewer->Set(id);
}

//=============================================================================
// 連打ゲームのゲージを設置する処理
//=============================================================================
void BeatGameViewer::SetGameGauge(float percent)
{
	gaugeViewer->Set(percent);
}

//=============================================================================
// 連打ゲームの残り時間を設定する処理
//=============================================================================
void BeatGameViewer::SetRemainTime(float time)
{
	timerViewer->Set(time);
}

//=============================================================================
// 「Ready」を表示する処理
//=============================================================================
void BeatGameViewer::SetReady(void)
{
	starterViewer->SetReady();
}

//=============================================================================
// 「GO」を表示する処理
//=============================================================================
void BeatGameViewer::SetGo(void)
{
	starterViewer->SetGo();
}

//=============================================================================
// 結果を表示する処理
//=============================================================================
void BeatGameViewer::SetResult(BeatResultViewer::ResultID id, std::function<void(void)> Callback)
{
	resultViewer->Set(id, Callback);
}
