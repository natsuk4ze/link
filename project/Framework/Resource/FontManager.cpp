//=====================================
//
//FontManager.cpp
//機能:フォントマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FontManager.h"

/**************************************
フォントリソース読み込み処理
***************************************/
void FontManager::LoadFont(const char* filePath)
{
	AddFontResource(filePath);
	loadFontContainer.push_back(filePath);
}

/**************************************
フォントリソース解放処理
***************************************/
void FontManager::RemoveFont(const char* filePath)
{
	RemoveFontResource(filePath);
}

/**************************************
フォント解放処理
***************************************/
void FontManager::ClearAll()
{
	for (auto&& pair : fontPool)
	{
		SAFE_RELEASE(pair.second);
	}
	fontPool.clear();

	for (auto&& pair : italicFontPool)
	{
		SAFE_RELEASE(pair.second);
	}
	italicFontPool.clear();

	for (auto&& path : loadFontContainer)
	{
		RemoveFont(path.c_str());
	}
}

/**************************************
フォント取得処理
***************************************/
LPD3DXFONT FontManager::GetFont(const std::string & fontName, int fontSize)
{
	const FontResourceKey Key = { fontName, fontSize };
	if (fontPool.count(Key) == 0)
		_CreateFont(fontName, fontSize);

	return fontPool[Key];
}

/**************************************
イタリックフォント取得処理
***************************************/
LPD3DXFONT FontManager::GetItalicFont(const std::string & fontName, int fontSize)
{
	const FontResourceKey Key = { fontName, fontSize };

	if (italicFontPool.count(Key) == 0)
		_CreateItalicFont(fontName, fontSize);

	return italicFontPool[Key];
}

/**************************************
フォント作成取得処理
***************************************/
void FontManager::_CreateFont(const std::string & name, int fontSize)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPD3DXFONT font = NULL;
	D3DXCreateFont(pDevice, fontSize, 0, 0, D3DX_DEFAULT, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T(name.c_str()), &font);
}

/**************************************
イタリックフォント作成処理
***************************************/
void FontManager::_CreateItalicFont(const std::string & name, int fontSize)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPD3DXFONT font = NULL;
	D3DXCreateFont(pDevice, fontSize, 0, 0, D3DX_DEFAULT, true, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T(name.c_str()), &font);
}

/**************************************
デストラクタ
***************************************/
FontManager::~FontManager()
{
	ClearAll();
}

/**************************************
FontResourceKeyコンストラクタ
***************************************/
FontResourceKey::FontResourceKey(std::string name, int size) :
	fontName(name),
	fontSize(size)
{

}

/**************************************
FontResourceKey比較演算子
***************************************/
bool FontResourceKey::operator<(const FontResourceKey & rhs) const
{
	return std::tie(fontName, fontSize) < std::tie(rhs.fontName, rhs.fontSize);
}
