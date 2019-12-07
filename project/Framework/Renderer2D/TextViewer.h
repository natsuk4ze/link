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
	//コンストラクタ
	//fontName : 使用するフォントの名前
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

	//座標ゲット処理
	D3DXVECTOR2 GetPosition(void) const;
	
	//フォント読み込み処理
	//自前のフォントを使用する場合にフォントを一時的にインストールする
	//fontFileName : インストールするフォントファイルへのパス
	static void LoadFont(const char* fontFileName);

	//フォントアンインストール処理
	//一時的にインストールした自前のフォントをアンインストールする
	//fontFileName : アンインストールフォントファイルへのパス
	static void RemoveFont(const char* fontFileName);

private:
	//フォントインターフェイス
	ID3DXFont * font;

	//フォントサイズ
	int fontSize;

	//表示座標
	int posX;
	int posY;

	//行数
	int lineNum;

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