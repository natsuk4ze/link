
//=============================================================================
//
// イベントメッセージ処理 [GuideCallOutViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUIDE_CALL_OUT_VIEWER_H_
#define _GUIDE_CALL_OUT_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GuideCallOutViewer :public BaseViewer
{
public:
	GuideCallOutViewer();
	~GuideCallOutViewer();

	void Update(void);
	void Draw(void);

	//メッセージセット
	void Set(const std::string &message);

	//メッセージセットカウンター
	int messageSetCnt;

	//再生中かどうか
	bool isPlaying;

private:

	BaseViewerDrawer * bg;
	TextViewer *text;

	//再生処理
	void Play();

	//フレームカウント
	int countFrame;
};

#endif