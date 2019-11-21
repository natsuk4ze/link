//=============================================================================
//
// 結果ランキングビュアー処理 [ResultRankingViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RANKING_VIEWER_H_
#define _RANKING_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultRankingViewer :public BaseViewer
{
public:
	ResultRankingViewer();
	~ResultRankingViewer();

	void Update(void);
	void Draw(void);

	//パラメータを受けとる箱
	float parameterBox;

private:
	CountViewerDrawer *num;
};

#endif