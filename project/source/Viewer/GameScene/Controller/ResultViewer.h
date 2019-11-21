//=============================================================================
//
// 結果ビュアーコントロール処理 [ResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_VIEWER_H_
#define _RESULT_VIEWER_H_

#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class ResultViewerParam;
class ResultRankingViewer;
class BaseViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultViewer
{
public:
	ResultViewer();
	~ResultViewer();

	void Update(void);
	void Draw(void);

	//パラメータ受け取り
	void ReceiveParam(ResultViewerParam&param);

	void SetActive(bool flag);

	std::vector <BaseViewer*> resultViewer;

private:

	ResultRankingViewer * rankingViewer;
	bool isActive;
};

#endif

