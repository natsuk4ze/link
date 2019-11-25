//=====================================
//
//デバッグウィンドウヘッダ[debugWindow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DEBUGWINDOW_H_
#define _DEBUGWINDOW_H_

#include "../../main.h"

#include <string>
#include <deque>

/**************************************
マクロ定義
***************************************/
#define USE_DEBUGFUNC
#define STR(var) #var		//varを文字列に置換するマクロ

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************/
//ImGUIラッパークラス
/***************************************/
class Debug
{
public:
	//開始、終了処理
	static void Begin(const char* label, bool menuBar = false);
	static void End();

	//Console表示
	static void Log(const char *str, ...);

	//テキスト表示
	static void Text(const char* str, ...);
	static void Text(const D3DXVECTOR3& arg, const char* name);

	//ボタン入力関連
	static bool Button(const char* label);
	static bool RadioButton(const char* label, int& out, int val);
	static bool CheckBox(const char* label, bool& val);
	
	//パラメータ入力関連
	static bool Input(const char* label, float& out);
	static bool Input(const char* label, int& out);
	static bool Input(const char* label, char* out, size_t sizeBuff);
	static bool Input(const char* label, D3DXVECTOR3& out);
	static bool Input(const char* label, D3DXVECTOR2& out);
	static bool Input(const char* label, std::string& out);

	//パラメータスライダー入力関連
	static bool Slider(const char* label, float& out, float min, float max);
	static bool Slider(const char* label, int& out, int min, int max);
	static bool Slider(const char* label, D3DXVECTOR3& out, const D3DXVECTOR3& min, const D3DXVECTOR3& max);
	static bool Slider(const char* label, D3DXVECTOR2& out, const D3DXVECTOR2& min, const D3DXVECTOR2& max);

	//テクスチャ描画
	static void DrawTexture(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2& size);

	//カラーエディタ
	static bool ColorEdit(const char* label, D3DXCOLOR& out);
	
	//プログレスバー
	static void ProgressBar(const char* label, float fraction, const D3DXVECTOR2& size = D3DXVECTOR2(-1.0f, 0.0f));

	//改行、同行
	static void NewLine();
	static void SameLine();

	//ツリー関連
	static void ExpandTree(bool isOpen);
	static bool PushTree(const char* label);
	static void PopTree();

	//メニューバー関連
	static bool BeginMenu();
	static void EndMenu();
	static bool BeginMenuItem(const char* label);
	static void EndMenuItem();
	template <class T>
	static void MenuItem(const char* label, T func)
	{
#ifdef USE_DEBUGFUNC
		if (ImGui::MenuItem(label))
		{
			func();
		}
#endif
	}

	//子要素関連
	static bool BeginChild(const char* label);
	static void EndChild();

	//各種処理
	static LRESULT WindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	static void Uninit();
	static void Update();
	static void Draw();

private:
	Debug();

	static const unsigned MaxLog;
	static std::deque<std::string> textLog;
};

#endif