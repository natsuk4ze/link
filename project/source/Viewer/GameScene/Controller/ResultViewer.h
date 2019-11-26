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
class ResultScoreViewer;
class ResultViewerParam;
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

	void SetActive(bool flag);

	//パラメータの受け取り処理
	void ReceiveParam(int cityScore,int worldScore,int spaceScore);

private:
	std::vector <BaseViewer*> resultViewer;
	ResultScoreViewer * scoreViewer;
	ResultViewerParam *viewerParam;

	bool isActive;
};

#endif

