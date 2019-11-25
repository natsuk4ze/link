//=============================================================================
//
// 結果スコアビュアー処理 [ResultScoreViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_SCORE_VIEWER_H_
#define _RESULT_SCORE_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultScoreViewer :public BaseViewer
{
private:
	const static int fieldTypeMax = 3;
	CountViewerDrawer * num[fieldTypeMax];

public:
	ResultScoreViewer();
	~ResultScoreViewer();

	void Update(void);
	void Draw(void);

	//パラメータを受けとる箱
	int parameterBox[fieldTypeMax];
};

#endif