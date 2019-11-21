//=============================================================================
//
// 結果ビュアーコントロール処理 [ResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../ResultViewer/ResultRankingViewer.h"
#include "../ParameterContainer/ResultViewerParam.h"
#include "ResultViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ResultViewer::ResultViewer()
{
	resultViewer.push_back(rankingViewer = new ResultRankingViewer());
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultViewer::~ResultViewer()
{
	//メモリを解放
	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		SAFE_DELETE(resultViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	resultViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultViewer::Update()
{
	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// パラメータ受け取り処理
//=============================================================================
void ResultViewer::ReceiveParam(ResultViewerParam &param)
{

}

//=============================================================================
// 描画可否判定のセット
//=============================================================================
void ResultViewer::SetActive(bool flag)
{
	isActive = flag;
}
