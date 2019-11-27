
//=============================================================================
//
// リザルト名前入力処理 [ResultNameEntryViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_NAME_ENTRY_VIEWER_H_
#define _RESULT_NAME_ENTRY_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultNameEntryViewer :public BaseViewer
{
public:
	ResultNameEntryViewer();
	~ResultNameEntryViewer();

	void Update();
	void Draw(void);

	//登録名取得処理
	std::string GetEntryName(void);

	//登録名
	std::string entryName;

private:

	//登録できる名前の最大数
	static const int entryNameMax = 3;

	//文字種の最大数
	static const int charTypeMax = 36;

	//文字
	BaseViewerDrawer * character[entryNameMax];

	//カーソル
	BaseViewerDrawer * cursor;

	//テクスチャのUVをセット
	void SetTexture();

	//カーソルの座標をセット
	void SetCursorPos();

	//名前入力処理
	void NameInput(void);

	//登録名セット処理
	void SetEntryName(int id);

	//文字ID
	int charID[entryNameMax];

	//文字カウント
	int charCnt;
};

#endif