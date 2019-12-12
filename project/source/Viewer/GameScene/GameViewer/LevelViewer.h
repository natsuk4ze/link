//=============================================================================
//
// AIレベルビュアー処理 [LevelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LEVEL_VIEWER_H_
#define _LEVEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CountViewerDrawer;
class CircleGauge;
class BaseViewerDrawer;
class RotateViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class LevelViewer :public BaseViewer
{
public:
	LevelViewer();
	~LevelViewer();

	void Update(void);
	void Draw(void);

	//AIレベルビュアーの種類
	enum LevelViewerType
	{
		LevelAI,
		RatioLevel,
		CurrentFieldLevel,
		Max
	};

	//パラメータを受けとる箱
	float parameterBox[Max];

private:

	const static int guageMax = 3;

	CircleGauge *circleGuage[guageMax];
	CountViewerDrawer *num;
	BaseViewerDrawer *bg;
	BaseViewerDrawer *text;
	BaseViewerDrawer *place;

	int currentFieldLevel;

	//数字ホッピング処理
	void HopNumber(void);

	//描画用ratioLevel設定
	void SetDrawingRatioLevel(void);

	//描画用ratioLevel増加
	void IncreaseDrawingRatioLevel(void);

	//描画用ratioLevel減少
	void DecreaseDrawingRatioLevel(void);

	//現在のパラメータ
	int currentParam[Max];

	//１フレーム前のパラメータ
	int lastParam[Max];

	//描画用ratioLevel
	float drawingRatioLevel;

	//LevelAIが増加中かどうか
	bool isLevelAI_Increasing;

	//LevelAIが減少中かどうか
	bool isLevelAI_Decreasing;
};

#endif