//=============================================================================
//
// 結果スコアビュアー処理 [ResultScoreViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "ResultScoreViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"

using std::to_string;
using std::string;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static const D3DXVECTOR2 scoreTextGapPos = D3DXVECTOR2(-120.0f,-40.0f);
static const D3DXVECTOR2 rewardTextGapPos = D3DXVECTOR2(-120.0f, 35.0f);
static const float fieldTelopGapPos = 200.0f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ResultScoreViewer::ResultScoreViewer() :
	isInPlaying(false),
	isOutPlaying(false)
{
	const D3DXCOLOR telopColor[telopMax] = {
		D3DXCOLOR(0.0f, 104 / 255.0f, 98 / 255.0f, 0.9f),
		D3DXCOLOR(118/255.0f,0.0f,0.0f,0.9f),
		D3DXCOLOR(118/255.0f,106/255.0f,0.0f,0.9f),
		D3DXCOLOR(0.0f,59/255.0f,104/255.0f,0.9f),
	};

	for (int i = 0; i < telopMax; i++)
	{
		bg[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2,SCREEN_HEIGHT / 10 * 1.70f +i* 250.0f),
			D3DXVECTOR2(1700.0f, 160.0f), "data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/ScoreBG.png");
		bg[i]->SetColor(telopColor[i]);

		fieldText[i] = new BaseViewerDrawer(D3DXVECTOR2(-SCREEN_WIDTH*2, bg[i]->position.y-120.0f),
			D3DXVECTOR2(1024 / 2.0f, 1024 / 8.0f),"data/TEXTURE/Viewer/ResultViewer/ResultScoreViewer/FieldText.png");
		fieldText[i]->SetTexture(1, 4,i);

		scoreText[i] = new TextViewer("マキナス 4 Square", 80);
		scoreText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y - 40.0f));
		scoreText[i]->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);

		rewardText[i] = new TextViewer("マキナス 4 Square", 40);
		rewardText[i]->SetPos((int)(-SCREEN_WIDTH*2), (int)(bg[i]->position.y + 40.0f));
		rewardText[i]->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);
	}

	anim[AnimType::TelopIn] = new ViewerAnimater();
	anim[AnimType::TelopOut] = new ViewerAnimater();
	std::vector<std::function<void()>> inVec = {
		[=] {
		//シティテロップスクリーンイン
		InCityTelop();
	},
		[=] {
		//ワールドテロップスクリーンイン
		InWorldTelop();	
	},
		[=] {
		//スペーステロップスクリーンイン
		InSpaceTelop();	
	},
		[=] {
		//リザルトテロップスクリーンイン
		InResultTelop();	
	}};
	std::vector<std::function<void()>> outVec = {
		[=] {
		//シティテロップスクリーンアウト
		OutCityTelop();
	},
		[=] {
		//ワールドテロップスクリーンアウト
		OutWorldTelop();
	},
		[=] {
		//スペーステロップスクリーンアウト
		OutSpaceTelop();
	},
		[=] {
		//リザルトテロップスクリーンアウト
		OutResultTelop();
	} };
	anim[AnimType::TelopIn]->SetAnimBehavior(inVec);
	anim[AnimType::TelopOut]->SetAnimBehavior(outVec);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultScoreViewer::~ResultScoreViewer()
{
	for (int i = 0; i < telopMax; i++)
	{
		SAFE_DELETE(bg[i]);
		SAFE_DELETE(fieldText[i]);
		SAFE_DELETE(rewardText[i]);
		SAFE_DELETE(scoreText[i]);
	}
	SAFE_DELETE(anim[AnimType::TelopIn]);
	SAFE_DELETE(anim[AnimType::TelopOut]);
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultScoreViewer::Update(void)
{
	if (isInPlaying)
	{
		anim[AnimType::TelopIn]->PlayAnim([=]
		{
			anim[AnimType::TelopIn]->SetPlayFinished(isInPlaying, [=]
			{
				if(this->CallbackInFin != nullptr)
					this->CallbackInFin();
			});
		});
	}
	if (isOutPlaying)
	{
		anim[AnimType::TelopOut]->PlayAnim([=]
		{
			anim[AnimType::TelopOut]->SetPlayFinished(isOutPlaying, [=]
			{
				//再生終了の通知
			});
		});
	}
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
		scoreText[i]->Draw();
	}
}

//=============================================================================
// 受け取ったパラメータをセットする処理
//=============================================================================
void ResultScoreViewer::ReceiveParam(const ResultViewerParam& ResultPara)
{
	string BuildRoad;
	string ConnectedCity;

	//引数でスコアを表示できるようにする
	// scoreText[0] = Total Result
	// scoreText[1] = City
	// scoreText[2] = World
	// scoreText[3] = Spcae

	// City Level
	scoreText[1]->SetText("スコア：" + to_string(ResultPara.score[City]));
	BuildRoad = "作った道の数　：" + to_string(ResultPara.builtRoad[City]);
	ConnectedCity = "繋がった街の数：" + to_string(ResultPara.connectedCity[City]);
	rewardText[1]->SetText(BuildRoad + "\n" + ConnectedCity);

	// World Level
	scoreText[2]->SetText("スコア：" + to_string(ResultPara.score[World]) + "万");
	BuildRoad = "作った道の数　：" + to_string(ResultPara.builtRoad[World]);
	ConnectedCity = "繋がった街の数：" + to_string(ResultPara.connectedCity[World]);
	rewardText[2]->SetText(BuildRoad + "\n" + ConnectedCity);

	// Space Level
	// 億
	int BillionNum = ResultPara.score[Space] % 10000;
	// 兆
	int TrillionNum = ResultPara.score[Space] / 10000;
	if (ResultPara.score[Space] <= 9999)
	{
		scoreText[3]->SetText("スコア：" + to_string(ResultPara.score[Space]) + "億");
	}
	else
	{
		scoreText[3]->SetText("スコア：" + to_string(TrillionNum) + "兆" + to_string(BillionNum) + "億");
	}
	BuildRoad = "作った道の数　：" + to_string(ResultPara.builtRoad[Space]);
	ConnectedCity = "繋がった街の数：" + to_string(ResultPara.connectedCity[Space]);
	rewardText[3]->SetText(BuildRoad + "\n" + ConnectedCity);

	// Total Result

	if (ResultPara.score[Space] > 9999)
	{
		string TotalScoreStr = 
			to_string(TrillionNum) + "兆" +
			to_string(BillionNum) + "億" +
			to_string(ResultPara.score[World]) + "万" +
			to_string(ResultPara.score[City]);
		scoreText[0]->SetText("合計スコア：" + TotalScoreStr);
	}
	else if (ResultPara.score[Space] > 0 && ResultPara.score[Space] < 9999)
	{
		string TotalScoreStr = 
			to_string(ResultPara.score[Space]) + "億" +
			to_string(ResultPara.score[World]) + "万" +
			to_string(ResultPara.score[City]);
		scoreText[0]->SetText("合計スコア：" + TotalScoreStr);
	}
	else if (ResultPara.score[Space] == 0 && ResultPara.score[World] != 0)
	{
		string TotalScoreStr =
			to_string(ResultPara.score[World]) + "万" +
			to_string(ResultPara.score[City]);
		scoreText[0]->SetText("合計スコア：" + TotalScoreStr);
	}
	else if (ResultPara.score[World] == 0 && ResultPara.score[City] != 0)
	{
		string TotalScoreStr = to_string(ResultPara.score[City]);
		scoreText[0]->SetText("合計スコア：" + TotalScoreStr);
	}
	else if (ResultPara.score[City] == 0)
	{
		scoreText[0]->SetText("合計スコア：0");
	}
	int TotalRoadNum = ResultPara.builtRoad[City] + ResultPara.builtRoad[World] + ResultPara.builtRoad[Space];
	int TotalCityNum = ResultPara.connectedCity[City] + ResultPara.connectedCity[World] + ResultPara.connectedCity[Space];
	BuildRoad = "作った道の数　：" + to_string(TotalRoadNum);
	ConnectedCity = "繋がった街の数：" + to_string(TotalCityNum);
	rewardText[0]->SetText(BuildRoad + "\n" + ConnectedCity);
}

//=============================================================================
// テロップ停止座標取得処理
//=============================================================================
void ResultScoreViewer::GetStopPos()
{
	for (int i = 0; i < telopMax; i++)
	{
		bgStopPos[i] = D3DXVECTOR2(bg[i]->position.x, bg[i]->position.y);
		fieldTextStopPos[i] = D3DXVECTOR2(fieldText[i]->position.x, fieldText[i]->position.y);
	}
}

//=============================================================================
// シティテロップスクリーンイン処理
//=============================================================================
void ResultScoreViewer::InCityTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 1;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc,[=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//カウントアップ処理
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ワールドテロップスクリーンイン処理
//=============================================================================
void ResultScoreViewer::InWorldTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f*2.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 2;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//カウントアップ処理
				});
			});
		}
		);
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// スペーステロップスクリーンイン処理
//=============================================================================
void ResultScoreViewer::InSpaceTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f*3.0f;
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 3;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX + fieldTelopGapPos, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//カウントアップ処理
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// リザルトテロップスクリーンイン処理
//=============================================================================
void ResultScoreViewer::InResultTelop()
{
	const float telopPosX = SCREEN_WIDTH / 15.0f*4.0f;	
	const float initPosX = -(telopPosX + SCREEN_WIDTH);
	const int index = 0;

	anim[AnimType::TelopIn]->Move(*bg[index], D3DXVECTOR2(initPosX, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 30.0f, OutCirc, [=]
	{
		anim[AnimType::TelopIn]->SubMove(*fieldText[index], D3DXVECTOR2(initPosX, fieldText[index]->position.y), D3DXVECTOR2(telopPosX - fieldTelopGapPos*1.70f, fieldText[index]->position.y), OutCirc, [=]
		{
			anim[AnimType::TelopIn]->SubFadeText(*scoreText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
			{
				anim[AnimType::TelopIn]->SubFadeText(*rewardText[index], 0.0f, 1.0f, 0.3f, OutCirc, [=]
				{
					//カウントアップ処理
				});
			});
		});
	});

	scoreText[index]->SetPos((int)(fieldText[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(fieldText[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// シティテロップスクリーンアウト処理
//=============================================================================
void ResultScoreViewer::OutCityTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 1;

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX/4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// ワールドテロップスクリーンアウト処理
//=============================================================================
void ResultScoreViewer::OutWorldTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 2;

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX / 4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// スペーステロップスクリーンアウト処理
//=============================================================================
void ResultScoreViewer::OutSpaceTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 3;

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX / 4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// リザルトテロップスクリーンアウト処理
//=============================================================================
void ResultScoreViewer::OutResultTelop()
{
	const float telopPosX = -SCREEN_WIDTH;
	const int index = 0;

	anim[AnimType::TelopOut]->Move(*bg[index], D3DXVECTOR2(bgStopPos[index].x, bg[index]->position.y), D3DXVECTOR2(telopPosX, bg[index]->position.y), 10.0f, InCirc, [=]
	{
		anim[AnimType::TelopOut]->SubMove(*fieldText[index], D3DXVECTOR2(fieldTextStopPos[index].x, fieldText[index]->position.y), D3DXVECTOR2(telopPosX/4 + fieldTelopGapPos, fieldText[index]->position.y), OutCirc);
	});

	scoreText[index]->SetPos((int)(bg[index]->position.x + scoreTextGapPos.x), (int)(bg[index]->position.y + scoreTextGapPos.y));
	rewardText[index]->SetPos((int)(bg[index]->position.x + rewardTextGapPos.x), (int)(bg[index]->position.y + rewardTextGapPos.y));
}

//=============================================================================
// テロップスクリーンイン処理
//=============================================================================
void ResultScoreViewer::SetTelopIn(std::function<void()> CallbackInFin)
{
	this->CallbackInFin = CallbackInFin;
	isInPlaying = true;
	anim[AnimType::TelopIn]->ResetAnim();
}

//=============================================================================
// テロップスクリーンアウト処理
//=============================================================================
void ResultScoreViewer::SetTelopOut()
{
	GetStopPos();
	isOutPlaying = true;
	anim[AnimType::TelopOut]->ResetAnim();
}

//=============================================================================
// テロップスクリーンイン再生中判定
//=============================================================================
bool ResultScoreViewer::IsPlayingIn() const
{
	return isInPlaying;
}

//=============================================================================
// テロップスクリーンアウト再生中判定
//=============================================================================
bool ResultScoreViewer::IsPlayingOut() const
{
	return isOutPlaying;
}