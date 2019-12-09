//=====================================
//
//TextViewer.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_

#include "../../main.h"

#include <string>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TextViewer : public GameObject
{
public:
	//コンストラクタ
	//fontName : 使用するフォントの名前 ※フォントファイルへのパスではないので注意
	//size : 表示フォントサイズ
	TextViewer(const char* fontName, int size);

	//デストラクタ
	~TextViewer();

	//描画処理
	void Draw();

	//座標セット処理
	void SetPos(int x, int y);

	//カラーセット処理
	void SetColor(const D3DXCOLOR& color);

	//表示テキストセット処理
	void SetText(const std::string& message);

	//イタリック使用設定
	void UseItalic(bool state);

private:
	//フォントインターフェイス
	LPD3DXFONT font;
	LPD3DXFONT italicFont;

	//フォントサイズ
	int fontSize;

	//表示座標
	int posX;
	int posY;

	//行数
	int lineNum;

	//表示カラー
	D3DXCOLOR color;

	//イタリック使用
	bool useItalic;

	//表示文字列
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif
};

#endif