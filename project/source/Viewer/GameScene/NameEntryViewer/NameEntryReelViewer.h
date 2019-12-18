//=============================================================================
//
// 名前入力リール処理 [NameEntryReelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_REEL_VIEWER_H_
#define _NAME_ENTRY_REEL_VIEWER_H_

#include <functional>
#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;
class ViewerAnimater;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NameEntryReelViewer :public BaseViewer
{
public:
	NameEntryReelViewer();
	~NameEntryReelViewer();

	void Update();
	void Draw(void);

	//リールアップ処理
	void ReelUp(int reelCnt);

	//リールダウン処理
	void ReelDown(int reelCnt);

	//リールの文字を取得する
	int* GetReelChar(void);

	bool MoveCursorRight(void);
	bool MoveCursorLeft(void);

	void SetTelopIn();
	void SetTelopOut();

	// カーソルが動けるかどうかのフラグを取得
	bool GetCursorMovable(void) { return this->CursorMovable; };

private:

	enum AnimScene
	{
		TelopIn,
		TelopOut,
		Max
	};

	//登録できる名前の最大数
	static const int entryNameMax = 3;

	//文字種の最大数
	static const int charTypeMax = 36;

	//リールに表示されている文字
	int character[entryNameMax];

	bool isInPlaying;
	bool isOutPlaying;

	// カーソルが移動できるかどうか
	bool CursorMovable;

	BaseViewerDrawer * reel[entryNameMax];
	BaseViewerDrawer * cursor;
	BaseViewerDrawer * bg;
	TextViewer *text;
	TextViewer *underBar;
	ViewerAnimater *anim[AnimScene::Max];

	void InReel(std::function<void()> Callback);
	void OutReel(std::function<void()> Callback);
};

#endif