//=====================================
//
//FontManager.h
//機能:フォントマネージャ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <map>
#include <vector>

/**************************************
FontResourceKeyクラス
***************************************/
class FontResourceKey
{
	std::string fontName;
	int fontSize;

public:
	FontResourceKey(std::string name, int size);

	bool operator < (const FontResourceKey& rhs) const;

};

/**************************************
クラス定義
***************************************/
class FontManager : public BaseSingleton<FontManager>
{
	friend class BaseSingleton<FontManager>;
public:

	void LoadFont(const char* filePath);
	void RemoveFont(const char* filePath);

	void ClearAll();

	LPD3DXFONT GetFont(const std::string& fontName, int fontSize);
	LPD3DXFONT GetItalicFont(const std::string& fontName, int fontSize);

private:
	void _CreateFont(const std::string& name, int fontSize);
	void _CreateItalicFont(const std::string& name, int fontSize);

	FontManager() {}
	FontManager(const FontManager&) {}

	~FontManager();
	
	std::map<FontResourceKey, LPD3DXFONT> fontPool;
	std::map<FontResourceKey, LPD3DXFONT> italicFontPool;
	std::vector<std::string> loadFontContainer;
};
#endif