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
class TextViewer
{
public:
	TextViewer(const char* fontName, int size);
	~TextViewer();

	void Draw();

	void SetPos(int x, int y);

	void SetColor(const D3DXCOLOR& color);

	void SetText(const std::string& message);

	static void LoadFont(const char* fontFileName);

private:
	//フォントインターフェイス
	ID3DXFont * font;

	//フォントサイズ
	int fontSize;

	//表示座標
	int posX;
	int posY;

	//表示カラー
	D3DXCOLOR color;

	//表示文字列
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif
};

#endif