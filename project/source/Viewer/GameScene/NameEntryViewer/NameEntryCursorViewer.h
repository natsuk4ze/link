//=============================================================================
//
// 名前入力カーソルビュアー処理 [NameEntryCursorViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_CURSOR_VIEWER_H_
#define _NAME_ENTRY_CURSOR_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NameEntryCursorViewer :public BaseViewer
{
public:
	NameEntryCursorViewer();
	~NameEntryCursorViewer();

	void Update();
	void Draw();

	//カーソルを右に移動
	void MoveCursorRight();

	//カーソルを左に移動
	void MoveCursorLeft();

private:

	//カーソル
	BaseViewerDrawer * cursor;
};
#endif