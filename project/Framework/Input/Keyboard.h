//=====================================
//
//キーボードヘッダ[Keyboard.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/
#define	NUM_KEY_MAX		(256)			// キー最大数

/**************************************
クラス定義
***************************************/
namespace Keyboard
{
	HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pInput);
	void Uninit();
	void Update();

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRepeat(int nKey);
	bool GetRelease(int nKey);
};

#endif	