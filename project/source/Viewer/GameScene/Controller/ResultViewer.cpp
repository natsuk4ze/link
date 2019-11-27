//=============================================================================
//
// 結果ビュアーコントロール処理 [ResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../Score/Score.h"
#include "../ResultViewer/ResultScoreViewer.h"
#include "../ResultViewer/ResultNameEntryViewer.h"
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
	viewerParam = new ResultViewerParam();
	resultViewer.push_back(scoreViewer = new ResultScoreViewer());
	resultViewer.push_back(nemeEntryViewer = new ResultNameEntryViewer());
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultViewer::~ResultViewer()
{
	SAFE_DELETE(viewerParam);

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
// パラメータ受け取る処理
//=============================================================================
void ResultViewer::ReceiveParam(int cityScore, int worldScore, int spaceScore)
{
	int param[ResultViewerParam::fieldTypeMax] = { cityScore ,worldScore ,spaceScore };

	for (int i = 0; i < ResultViewerParam::fieldTypeMax; i++)
	{
		//コンテナに入れて
		viewerParam->score[i] = param[i];

		//コンテナからビュアーに渡す
		scoreViewer->parameterBox[i] = viewerParam->score[i];
	}
}

//=============================================================================
// 描画可否判定のセット
//=============================================================================
void ResultViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=============================================================================
// 登録名取得処理
//=============================================================================
std::string ResultViewer::GetEntryName()
{
	return nemeEntryViewer->entryName;
}
