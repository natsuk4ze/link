//=====================================
//
//マウスヘッダ[Mouse.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Mouse
{
public:
	Mouse();
	~Mouse();

	HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pInput);
	HRESULT Update();

	static BOOL GetPressLeft(void);      // 左クリックした状態
	static BOOL GetTriggerLeft(void);    // 左クリックした瞬間
	static BOOL GetPressRight(void);     // 右クリックした状態
	static BOOL GetTriggerRight(void);   // 右クリックした瞬間
	static BOOL GetPressCenter(void);    // 中クリックした状態
	static BOOL GetTriggerCenter(void);  // 中クリックした瞬間
	static float GetX(void);               // マウスがX方向に動いた相対値
	static float GetY(void);               // マウスがY方向に動いた相対値
	static float GetZ(void);               // マウスホイールが動いた相対値

	static D3DXVECTOR3 GetMousePosition(HWND hWnd);

private:
	static Mouse* mInstance ;
	LPDIRECTINPUTDEVICE8 pMouse = NULL; // mouse

	DIMOUSESTATE2   mouseState;		// マウスのダイレクトな状態
	DIMOUSESTATE2   mouseTrigger;	// 押された瞬間だけON
};
/**************************************
プロトタイプ宣言
***************************************/


#endif