//=============================================================================
//
// 名前入力背景処理 [NameEntryBgViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_BG_VIEWER_H_
#define _NAME_ENTRY_BG_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NameEntryBgViewer :public BaseViewer
{
public:
	NameEntryBgViewer();
	~NameEntryBgViewer();

	void Update();
	void Draw(void);

private:
	BaseViewerDrawer * congratsText;
	BaseViewerDrawer * newRecordText;
	BaseViewerDrawer * crown;

	void AnimTexture(void);

	int currentTexPattern;
};
#endif