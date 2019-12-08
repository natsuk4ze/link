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
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FontManager : public BaseSingleton<FontManager>
{
	friend class BaseSingleton<FontManager>;
public:

	void LoadFont(const char* filePath);
	void RemoveFont(const char* filePath);

	void CleaaAll();

	LPD3DXFONT GetFont(const std::string& fontName);
	LPD3DXFONT GetItalicFont(const std::string& fontName);

private:
	void _CreateFont(const std::string& name);
	void _CreateItalicFont(const std::string& name);

	FontManager() {}
	FontManager(const FontManager&) {}

	~FontManager();
	
	std::map<std::string, LPD3DXFONT> fontPool;
	std::map<std::string, LPD3DXFONT> italicFontPool;
	std::vector<std::string> loadFontContainer;
};
#endif