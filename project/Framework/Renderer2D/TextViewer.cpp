//=====================================
//
//TextViewer.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TextViewer.h"

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
	text("")
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateFont(pDevice, fontSize, 0, 0, D3DX_DEFAULT, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T(fontName), &font);
}

/**************************************
デストラクタ
***************************************/
TextViewer::~TextViewer()
{
	SAFE_RELEASE(font);
}

/**************************************
描画処理
***************************************/
void TextViewer::Draw()
{
	//テキストを中央寄せで表示するためのRectを計算
	LONG left = posX - text.length() * fontSize / 2;
	LONG top =  posY - fontSize / 2 *lineNum;
	LONG right = left + text.length() * fontSize;
	LONG bottom = top + fontSize *lineNum;

	//描画
	RECT rect = { left, top, right, bottom};
	font->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER, color);
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

//=============================================================================
// 座標ゲット処理
//=============================================================================
D3DXVECTOR2 TextViewer::GetPosition(void) const
{
	return D3DXVECTOR2((float)this->posX, (float)this->posY);
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
フォントロード処理
***************************************/
void TextViewer::LoadFont(const char * fontFileName)
{
	AddFontResource(fontFileName);
}

/**************************************
フォントリムーブ処理
***************************************/
void TextViewer::RemoveFont(const char * fontFileName)
{
	RemoveFontResource(fontFileName);
}
