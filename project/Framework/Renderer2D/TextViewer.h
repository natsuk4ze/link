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
	
	//水平方向のレイアウト
	enum class HorizontalAlignment
	{
		Left = 0x00,		//左寄せ
		Center = 0x01,		//中央寄せ
		Right = 0x02		//右寄せ
	};

	//垂直方向のレイアウト
	enum class VerticalAlignment
	{
		Top = 0x00,			//上寄せ
		Center = 0x04,		//中央寄せ
		Bottom = 0x08		//下寄せ
	};
	
	//コンストラクタ
	//fontName : 使用するフォントの名前 ※フォントファイルへのパスではないので注意
	//size : 表示フォントサイズ
	TextViewer(const char* fontName, int size);

	//デストラクタ
	~TextViewer();

	//描画処理
	void Draw(void);

	//座標セット処理
	void SetPos(int x, int y);

	//カラーセット処理
	void SetColor(const D3DXCOLOR& color);

	//表示テキストセット処理
	void SetText(const std::string& message);

	//表示テキスト取得処理
	std::string GetText() const;

	//イタリック使用設定
	void UseItalic(bool state);

	//水平方向のレイアウト設定
	void SetHorizontalAlignment(HorizontalAlignment alignment);

	//垂直方向のレイアウト設定
	void SetVerticalAlignment(VerticalAlignment alignment);

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

	//レイアウト
	HorizontalAlignment horizontal;
	VerticalAlignment vertical;

	//表示文字列
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif

	//Rect計算処理
	RECT GetRect() const;
};

#endif