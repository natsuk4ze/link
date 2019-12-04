//=============================================================================
//
// 結果スコアビュアー処理 [ResultScoreViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "ResultScoreViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :
	parameterBox()
{
	const float intervalPosTelop = 230.0f;
	const float intervalPosNum = 400.0f;

	const D3DXVECTOR2 telopSize[telopMax] = {
		D3DXVECTOR2(2300.0f, 230.0f),
		D3DXVECTOR2(1600.0f, 160.0f),
		D3DXVECTOR2(1600.0f, 160.0f),
		D3DXVECTOR2(1600.0f, 160.0f)
	};
	const D3DXCOLOR telopColor[telopMax] = {
		D3DXCOLOR(0.0f,104/255.0f,98/255.0f,0.9f),
		D3DXCOLOR(118/255.0f,0.0f,0.0f,0.9f),
		D3DXCOLOR(118/255.0f,106/255.0f,0.0f,0.9f),
		D3DXCOLOR(0.0f,59/255.0f,104/255.0f,0.9f),
	};

	for (int i = 0; i < telopMax; i++)
	{
		totalScoreNum[i] = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 + i* intervalPosNum, SCREEN_HEIGHT / 10 * 2.5f),
			D3DXVECTOR2(80.0f, 80.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png", 80.0f, 0.1f, 4);

		bg[i] = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10.0f*1.0f, SCREEN_HEIGHT / 10 * 2.5f + i * intervalPosTelop),
			telopSize[i], "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultScoreViewer::~ResultScoreViewer()
{
	for (int i = 0; i < telopMax; i++)
	{
		SAFE_DELETE(totalScoreNum[i]);
		SAFE_DELETE(bg[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultScoreViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultScoreViewer::Draw(void)
{
	for (int i = 0; i < telopMax; i++)
	{
		bg[i]->Draw();

		if (i == 0)
		{
			//0表示なし
			totalScoreNum[i]->DrawCounter(totalScoreNum[i]->baseNumber,
				parameterBox[i], totalScoreNum[i]->intervalPosScr, totalScoreNum[i]->intervalPosTex);
		}
		else
		{
			//0表示
			totalScoreNum[i]->DrawCounter(totalScoreNum[i]->baseNumber, parameterBox[i], totalScoreNum[i]->placeMax,
				totalScoreNum[i]->intervalPosScr, totalScoreNum[i]->intervalPosTex);
		}
	}
}
