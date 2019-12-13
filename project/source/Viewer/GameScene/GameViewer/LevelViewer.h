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
	enum FieldType
	{
		City,
		World,
		Space
	};

	const static int guageMax = 3;

	CircleGauge *circleGuage[guageMax];
	CountViewerDrawer *num;
	CountViewerDrawer *overflowNum;
	BaseViewerDrawer *bg;
	BaseViewerDrawer *text;
	BaseViewerDrawer *plus;
	BaseViewerDrawer *place;

	//数字ホッピング処理
	void HopNumber(void);

	//ゲージ割合セット
	void SetGaugePer(void);

	//描画用ratioLevel設定
	void SetDrawingRatioLevel(void);

	//描画用ratioLevel増加
	void IncreaseDrawingRatioLevel(void);

	//描画用ratioLevel減少
	void DecreaseDrawingRatioLevel(void);

	//漢数字の桁のテクスチャをセットする
	void SetPlaceTex(void);

	//オーバーフローしてるかどうかを返す
	bool IsOverflowed(void);

	//描画用ratioLevel
	float drawingRatioLevel;
};

#endif