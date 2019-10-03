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
namespace Mouse
{
	HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pInput);
	void Uninit();
	HRESULT Update();

	 BOOL GetPressLeft(void);      // 左クリックした状態
	 BOOL GetTriggerLeft(void);    // 左クリックした瞬間
	 BOOL GetPressRight(void);     // 右クリックした状態
	 BOOL GetTriggerRight(void);   // 右クリックした瞬間
	 BOOL GetPressCenter(void);    // 中クリックした状態
	 BOOL GetTriggerCenter(void);  // 中クリックした瞬間
	 float GetX(void);               // マウスがX方向に動いた相対値
	 float GetY(void);               // マウスがY方向に動いた相対値
	 float GetZ(void);               // マウスホイールが動いた相対値

	 D3DXVECTOR3 GetMousePosition();
};

#endif