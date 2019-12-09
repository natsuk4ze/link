//=====================================
//
//TextViewer.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TextViewer.h"
#include "../Resource/FontManager.h"

/**************************************
コンストラクタ
***************************************/
TextViewer::TextViewer(const char * fontName, int fontSize) :
	font(NULL),
	fontSize(fontSize),
	posX(10),
	posY(10),
	lineNum(1),
	color(0xffffffff),
	text(""),
	useItalic(false)
{
	font = FontManager::Instance()->GetFont(fontName, fontSize);
	italicFont = FontManager::Instance()->GetItalicFont(fontName, fontSize);
}

/**************************************
デストラクタ
***************************************/
TextViewer::~TextViewer()
{
	SAFE_RELEASE(font);
	SAFE_RELEASE(italicFont);
}

/**************************************
描画処理
***************************************/
void TextViewer::Draw(bool FromLeft)
{
	if (!FromLeft)
	{
		//テキストを中央寄せで表示するためのRectを計算
		LONG left = posX - text.length() * fontSize / 2;
		LONG top = posY - fontSize / 2 * lineNum;
		LONG right = left + text.length() * fontSize;
		LONG bottom = top + fontSize * lineNum;

		//描画
		RECT rect = { left, top, right, bottom };

		if (!useItalic)
			font->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_NOCLIP, color);
		else
			italicFont->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_NOCLIP, color);
	}
	else
	{
		//テキストを左詰めで表示するためのRectを計算
		LONG left = posX;
		LONG top = posY - fontSize / 2 * lineNum;
		LONG right = left + text.length() * fontSize;
		LONG bottom = top + fontSize * lineNum;

		//描画
		RECT rect = { left, top, right, bottom };
		font->DrawText(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_VCENTER, color);
	}
}

/**************************************
座標セット処理
***************************************/
void TextViewer::SetPos(int x, int y)
{
	posX = x;
	posY = y;
}

/**************************************
座標セット処理
***************************************/
void TextViewer::SetColor(const D3DXCOLOR & color)
{
	this->color = color;
}

/**************************************
テキストセット処理
***************************************/
void TextViewer::SetText(const std::string & message)
{
	//改行を検索して行数をセット
	lineNum = 1 + (std::count(message.cbegin(), message.cend(), '\n'));

	text = message;
}

/**************************************
イタリック使用設定
***************************************/
void TextViewer::UseItalic(bool state)
{
	useItalic = state;
}
