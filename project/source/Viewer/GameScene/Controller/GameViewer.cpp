//=============================================================================
//
// Gameビュアー管理処理 [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../GameViewer/ItemStockViewer.h"
#include "../GameViewer/TimerViewer.h"
#include "../GameViewer/LevelViewer.h"
#include "../GameViewer/GradeUpViewer.h"
#include "../GameViewer/GradeFrameViewer.h"
#include "../GameViewer/GradeNameViewer.h"
#include "../ParameterContainer/GameViewerParam.h"
#include "GameViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GameViewer::GameViewer()
{
	gameViewer.push_back(stockViewer = new ItemStockViewer());
	gameViewer.push_back(timerViewer = new TimerViewer());
	gameViewer.push_back(levelViewer = new LevelViewer());
	gameViewer.push_back(gradeUpViewer = new GradeUpViewer());
	gameViewer.push_back(gradeFrameViewer = new GradeFrameViewer());
	gameViewer.push_back(gradeNameViewer = new GradeNameViewer());
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameViewer::~GameViewer()
{
	//メモリを解放
	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		SAFE_DELETE(gameViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	gameViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void GameViewer::Update()
{
	Debug::Begin("GradeUp");
	if (Debug::Button("GradeUp"))
		gradeUpViewer->SetGradeUp();
	if (Debug::Button("Slide"))
		gradeFrameViewer->SlideIn();
	Debug::End();

	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		gameViewer[i]->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void GameViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		gameViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// パラメータ受け取り処理
//=============================================================================
void GameViewer::ReceiveParam(GameViewerParam &param)
{
	//ストックビュアー
	stockViewer->parameterBox = param.stockNum;

	//タイマービュアー
	timerViewer->parameterBox = param.remainTime;

	//AIレベルビュアー
	levelViewer->parameterBox[levelViewer->LevelAI] = (float)param.levelAI;
	levelViewer->parameterBox[levelViewer->RatioLevel] = param.ratioLevel;
}

//=============================================================================
// 描画可否判定のセット
//=============================================================================
void GameViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=============================================================================
// 特定ビューア描画可否判定のセット
//=============================================================================
void GameViewer::SetActive(bool flag, ViewerNo viewer)
{
	gameViewer.at(viewer)->isPlaying = flag;
}

//=============================================================================
// グレードアップ演出
//=============================================================================
void GameViewer::SetGradeUp(std::function<void(void)> Callback)
{
	// レベルビューアの描画を停止
	SetActive(false, ViewerNo::Level);

	gradeUpViewer->SetGradeUp([=]()
	{
		// レベルビューアの描画を復帰
		SetActive(true, ViewerNo::Level);
		Callback();
	});
}
