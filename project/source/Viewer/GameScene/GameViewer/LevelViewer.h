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

	//矢印のID
	enum ArrowID
	{
		LevelUp,
		LevelDown,
	};

	//AIレベルビュアーの種類
	enum StockViewerType
	{
		LevelAI,
		RatioLevel,
	};

	//AIレベルビュアーの種類数
	static const int typeMax = 2;

	//パラメータを受けとる箱
	float parameterBox[typeMax];

private:

	//円ゲージ
	CircleGauge *circleGuage;

	//数字
	CountViewerDrawer *num;

	//背景
	BaseViewerDrawer *bg;

	//矢印
	RotateViewerDrawer *arrow;

	//矢印のテクスチャ情報コンテナ
	std::vector <LPDIRECT3DTEXTURE9> arrowTexContainer;

	//数字ホッピング処理
	void HopNumber(void);

	//描画用ratioLevel設定
	void SetDrawingRatioLevel(void);

	//描画用ratioLevel増加
	void IncreaseDrawingRatioLevel(void);

	//描画用ratioLevel減少
	void DecreaseDrawingRatioLevel(void);

	//矢印のテクスチャ情報受け渡し
	void PassArrowTexture(ArrowID id);

	//矢印のセット処理
	void SetArrow(ArrowID id);

	//矢印の上下処理
	void UpDownArrow();

	//現在のパラメータ
	int currentParam[typeMax];

	//１フレーム前のパラメータ
	int lastParam[typeMax];

	//描画用ratioLevel
	float drawingRatioLevel;

	//LevelAIが増加中かどうか
	bool isLevelAI_Increasing;

	//LevelAIが減少中かどうか
	bool isLevelAI_Decreasing;

	//矢印が再生中かどうか
	bool isArrowPlaying;

	//矢印上下処理用のラジアン
	float radian = 0.0f;
};

#endif