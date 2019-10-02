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
	color(0xffffffff),
	text("text")
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
	LONG left = posX - text.length() * fontSize / 2;
	LONG top =  posY - fontSize / 2;
	LONG right = left + text.length() * fontSize;
	LONG bottom = top + fontSize;

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

/**************************************
テキストセット処理
***************************************/
void TextViewer::SetText(const std::string & message)
{
	text = message;
}

/**************************************
テキストセット処理
***************************************/
void TextViewer::LoadFont(const char * fontFileName)
{
	AddFontResource(fontFileName);
}
