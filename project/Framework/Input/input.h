//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "../../main.h"
#include "Gamepad.h"
#include "Mouse.h"
#include "Keyboard.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Input
{
	friend class BaseGame;
public:
	Input();
	~Input();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Update();

	static float GetPressHorizontail(int no = 0);
	static float GetPressVertical(int no = 0);
	static float GetRepeatHorizontal(int no = 0);
	static float GetRepeatVertical(int no = 0);

private:
	LPDIRECTINPUT8 pDInput;					// IDirectInput8インターフェースへのポインタ
	GamePad *pad;
	Keyboard *keyboard;
	Mouse *mouse;

	static Input* mInstance;
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif