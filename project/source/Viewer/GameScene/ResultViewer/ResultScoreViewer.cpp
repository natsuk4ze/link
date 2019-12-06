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
	score(),
	completeRewardNum(),
	parameterBox()
{
	const float intervalPosTelop = 240.0f;
	const float intervalPosNum = 320.0f;

	const D3DXVECTOR2 telopSize[telopMax] = {
		D3DXVECTOR2(1600.0f*1.30f, 160.0f*1.30f),
		D3DXVECTOR2(1600.0f, 160.0f),
		D3DXVECTOR2(1600.0f, 160.0f),
		D3DXVECTOR2(1600.0f, 160.0f)
	};
	const D3DXVECTOR2 placeTextPos[scoreTelopMax] = {
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 4.0f,SCREEN_HEIGHT / 10 * 4.150f + 1 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 4.0f,SCREEN_HEIGHT / 10 * 4.150f + 2 * intervalPosTelop),
		D3DXVECTOR2(-SCREEN_WIDTH,0.0f)
	};
	const D3DXCOLOR telopColor[telopMax] = {
		D3DXCOLOR(0.0f, 104 / 255.0f, 98 / 255.0f, 0.9f),
		D3DXCOLOR(118/255.0f,0.0f,0.0f,0.9f),
		D3DXCOLOR(118/255.0f,106/255.0f,0.0f,0.9f),
		D3DXCOLOR(0.0f,59/255.0f,104/255.0f,0.9f),
	};
	const D3DXVECTOR2 telopPos[telopMax] = {
		D3DXVECTOR2(SCREEN_WIDTH / 10.0f*2.50f, SCREEN_HEIGHT / 10 * 4.50f - intervalPosTelop - (160.0f*1.30f - 160.0f) / 2),
		D3DXVECTOR2(SCREEN_WIDTH / 10.0f, SCREEN_HEIGHT / 10 * 4.50f + (0 * intervalPosTelop)),
		D3DXVECTOR2(SCREEN_WIDTH / 10.0f*1.50f, SCREEN_HEIGHT / 10 * 4.50f + (1 * intervalPosTelop)),
		D3DXVECTOR2(SCREEN_WIDTH / 10.0f*2.0f, SCREEN_HEIGHT / 10 * 4.50f + (2 * intervalPosTelop)),
	};
	const D3DXVECTOR2 fieldTextPos[telopMax] = {
		D3DXVECTOR2(SCREEN_WIDTH / 10* 1.0f+50.0f, SCREEN_HEIGHT / 10 * 3.30f - intervalPosTelop - (1024 / 8.0f*1.30f - 1024 / 8.0f) - 20.0f),
		D3DXVECTOR2(SCREEN_WIDTH / 10* 1.5f+50.0f, SCREEN_HEIGHT / 10 * 3.30f + 0 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10* 2.0f+50.0f, SCREEN_HEIGHT / 10 * 3.30f + 1 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10* 2.5f+50.0f, SCREEN_HEIGHT / 10 * 3.30f + 2 * intervalPosTelop)
	};
	const D3DXVECTOR2 fieldTextSize[telopMax] = {
		D3DXVECTOR2(1024 / 2.0f*1.30f, 1024 / 8.0f*1.30f),
		D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),
		D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),
		D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f)
	};
	const D3DXVECTOR2 rewardTextSize[telopMax] = {
		D3DXVECTOR2(300.0f*1.30f, 150.0f*1.30f),
		D3DXVECTOR2(300.0f, 150.0f),
		D3DXVECTOR2(300.0f, 150.0f),
		D3DXVECTOR2(300.0f, 150.0f)
	};
	const D3DXVECTOR2 rewardTextPos[telopMax] = {
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 1.0f, SCREEN_HEIGHT / 10 * 4.90f - 1.020f * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 1.5f, SCREEN_HEIGHT / 10 * 4.90f + 0 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 2.0f, SCREEN_HEIGHT / 10 * 4.90f + 1 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 2.5f, SCREEN_HEIGHT / 10 * 4.90f + 2 * intervalPosTelop)
	};
	const D3DXVECTOR2 rewardNumPos[telopMax] = {
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 1.0f+220.0f, SCREEN_HEIGHT / 10 * 4.85f - 1.020f * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 1.5f+220.0f, SCREEN_HEIGHT / 10 * 4.85f + 0 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 2.0f+220.0f, SCREEN_HEIGHT / 10 * 4.85f + 1 * intervalPosTelop),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 2.5f+220.0f, SCREEN_HEIGHT / 10 * 4.85f + 2 * intervalPosTelop),
	};
	const D3DXVECTOR2 rewardNumSize[telopMax] = {
		D3DXVECTOR2(70.0f*1.30f, 70.0f*1.30f),
		D3DXVECTOR2(70.0f, 70.0f),
		D3DXVECTOR2(70.0f, 70.0f),
		D3DXVECTOR2(70.0f, 70.0f)
	};

	for (int i = 0; i < telopMax; i++)
	{
		totalScoreNum[i] = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH/1.60f - i* intervalPosNum, SCREEN_HEIGHT / 10 * 1.60f),
			D3DXVECTOR2(70.0f*1.30f, 70.0f*1.30f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png", 60.0f, 0.1f, 4);

		bg[i] = new BaseViewerDrawer(telopPos[i],
			telopSize[i], "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);

		fieldText[i] = new BaseViewerDrawer(fieldTextPos[i],
			fieldTextSize[i], "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/FieldText.png");
		fieldText[i]->SetTexture(1, 4,i);

		rewardText[i] = new BaseViewerDrawer(rewardTextPos[i],
			rewardTextSize[i], "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/HeadText.png");
		rewardText[i]->SetTexture(1, 2, 1);

		rewardNum[i] = new CountViewerDrawer(rewardNumPos[i],
			rewardNumSize[i], "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png", 50.0f, 0.1f, 4);
	}
	for (int i = 0; i < totalScorePlaceTextMax; i++)
	{
		totalScorePlaceText[i] = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 1.60f -(i * intervalPosNum) - (totalScoreNum[i]->placeMax*totalScoreNum[i]->intervalPosScr)-10.0f, SCREEN_HEIGHT / 10 * 1.60f),
			D3DXVECTOR2(80.0f*1.30f, 80.0f*1.30f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/PlaceText.png");
		totalScorePlaceText[i]->SetTexture(2, 2, i);
	}
	for (int i = 0; i < scoreTelopMax; i++)
	{
		placeText[i] = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 * (1 + 0.5f*i)+550.0f, SCREEN_HEIGHT / 10 * 4.150f + (i+1) * intervalPosTelop),
			D3DXVECTOR2(80.0f, 80.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/PlaceText.png");

		scoreText[i] = new BaseViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10 *(1+0.5f*i)+100.0f, SCREEN_HEIGHT / 10 * 4.10f + i * intervalPosTelop),
			D3DXVECTOR2(300.0f, 150.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/HeadText.png");

		scoreNum[i] = new CountViewerDrawer(D3DXVECTOR2(SCREEN_WIDTH / 10*(1 + 0.5f*i)+400.0f, SCREEN_HEIGHT / 10 * 4.150f + i * intervalPosTelop),
			D3DXVECTOR2(70.0f, 70.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/Number.png", 50.0f, 0.1f, 4);

		placeText[i]->SetTexture(2, 2,i);
		scoreText[i]->SetTexture(1, 2, 0);
	}

	parameterBox[0] = 9999;
	parameterBox[1] = 9999;
	parameterBox[2] = 99999999;

	//city
	score[0] = parameterBox[0];
	//world
	score[1] = parameterBox[1];
	//space
	score[2] = parameterBox[2]%99990000;
	//overflow
	score[3] = (int)parameterBox[2]/10000;
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
		SAFE_DELETE(fieldText[i]);
		SAFE_DELETE(rewardText[i]);
		SAFE_DELETE(rewardNum[i]);
	}
	for (int i = 0; i < scoreTelopMax; i++)
	{
		SAFE_DELETE(placeText[i]);
		SAFE_DELETE(scoreText[i]);
		SAFE_DELETE(scoreNum[i]);
	}
	for (int i = 0; i < totalScorePlaceTextMax; i++)
	{
		SAFE_DELETE(totalScorePlaceText[i]);
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
		fieldText[i]->Draw();
		rewardText[i]->Draw();
		rewardNum[i]->DrawCounter(rewardNum[i]->baseNumber,
			completeRewardNum[i], rewardNum[i]->intervalPosScr, rewardNum[i]->intervalPosTex);
		totalScoreNum[i]->DrawCounter(totalScoreNum[i]->baseNumber,
			score[i], totalScoreNum[i]->intervalPosScr, totalScoreNum[i]->intervalPosTex);
	}
	for (int i = 0; i < scoreTelopMax; i++)
	{
		scoreText[i]->Draw();
		scoreNum[i]->DrawCounter(scoreNum[i]->baseNumber,
			score[i], scoreNum[i]->intervalPosScr, scoreNum[i]->intervalPosTex);
	}
	for (int i = 0; i < scoreTelopMax; i++)
	{
		placeText[i]->Draw();
	}
	for (int i = 0; i < totalScorePlaceTextMax; i++)
	{
		totalScorePlaceText[i]->Draw();
	}
}