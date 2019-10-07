//=============================================================================
//
// Gameビュアー管理処理 [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include <vector>
#include "StockViewer.h"
#include "TimerViewer.h"
#include "LevelViewer.h"
#include "GameViewerParam.h"
#include "GameViewer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static std::vector <BaseViewer*> baseViewer{};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GameViewer::GameViewer()
{
	baseViewer.push_back(stockViewer = new StockViewer());
	baseViewer.push_back(timerViewer = new TimerViewer());
	baseViewer.push_back(levelViewer = new LevelViewer());

	baseViewerMax = baseViewer.size();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameViewer::~GameViewer()
{
	baseViewer.clear();

	SAFE_DELETE(stockViewer);
	SAFE_DELETE(timerViewer);
	SAFE_DELETE(levelViewer);
}

//=============================================================================
// 更新処理
//=============================================================================
void GameViewer::Update()
{
	for (int i = 0; i < baseViewerMax; i++)
	{
		baseViewer[i]->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void GameViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < baseViewerMax; i++)
	{
		baseViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

//=============================================================================
// パラメータ受け取り処理
//=============================================================================
void GameViewer::ReceiveParam()
{

}
