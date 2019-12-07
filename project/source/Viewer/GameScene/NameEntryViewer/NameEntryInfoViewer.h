//=============================================================================
//
// 名前入力情報処理 [NameEntryInfoViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_INFO_VIEWER_H_
#define _NAME_ENTRY_INFO_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NameEntryInfoViewer :public BaseViewer
{
public:
	NameEntryInfoViewer();
	~NameEntryInfoViewer();

	void Update();
	void Draw(void);

private:
	BaseViewerDrawer * bg;
	TextViewer *text;
	TextViewer *underBar;
};
#endif