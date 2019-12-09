//=============================================================================
//
// 結果スコアビュアー処理 [ResultScoreViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_SCORE_VIEWER_H_
#define _RESULT_SCORE_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class ViewerAnimater;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultScoreViewer :public BaseViewer
{
private:
	enum AnimLayer
	{
		TelopIn,
		TelopOut,
		Max
	};
	const static int telopMax = 4;

	BaseViewerDrawer *bg[telopMax];
	BaseViewerDrawer*fieldText[telopMax];
	TextViewer *scoreText[telopMax];
	TextViewer *rewardText[telopMax];
	ViewerAnimater*anim[Max];

	int score[telopMax];
	int completeRewardNum[telopMax];

	//テロップスクリーンイン
	void InCityTelop();
	void InWorldTelop();
	void InSpaceTelop();
	void InResultTelop();

	//テロップスクリーンアウト
	void OutCityTelop();
	void OutWorldTelop();
	void OutSpaceTelop();
	void OutResultTelop();

	//止まった座標
	D3DXVECTOR2 bgStopPos[telopMax];
	D3DXVECTOR2 fieldTextStopPos[telopMax];

	void GetStopPos();
	void SetText();

	bool isInPlaying;
	bool isOutPlaying;

public:
	ResultScoreViewer();
	~ResultScoreViewer();

	void Update(void);
	void Draw(void);

	void SetTelopIn();
	void SetTelopOut();

	bool IsPlayingIn() const;
	bool IsPlayingOut() const;

	//パラメータを受けとる箱
	int parameterBox[3];
};

#endif