//=============================================================================
//
// “ü—Íˆ— [input.h]
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
// ƒNƒ‰ƒX’è‹`
//*****************************************************************************
namespace Input
{
	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit();
	void Update();

	float GetPressHorizontail(int no = 0);
	float GetPressVertical(int no = 0);

	float GetTriggerHorizontal(int no = 0);
	float GetTriggerVertical(int no = 0);

	float GetRepeatHorizontal(int no = 0);
	float GetRepeatVertical(int no = 0);
};

#endif