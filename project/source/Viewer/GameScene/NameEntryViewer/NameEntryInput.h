
//=============================================================================
//
// 名前入力インプット処理 [NameEntryInput.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _NAME_ENTRY_INPUT_H_
#define _NAME_ENTRY_INPUT_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class NameEntryInput
{
public:
	NameEntryInput();
	~NameEntryInput();

	//リールアップ入力取得処理
	bool GetReelUp(void);
	//リールダウン入力取得処理
	bool GetReelDown(void);
	//カーソル左移動入力取得処理
	bool GetCursorRight(void);
	//カーソル右移動入力取得処理
	bool GetCursorLeft(void);
	//エントリー終了入力取得処理
	bool GetFinishedEntry(void);
};

#endif