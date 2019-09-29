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
class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pInput);
	void Update();

	static bool GetPress(int nKey);
	static bool GetTrigger(int nKey);
	static bool GetRepeat(int nKey);
	static bool GetRelease(int nKey);

private:
	LPDIRECTINPUTDEVICE8 m_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
	BYTE	m_aKeyState[NUM_KEY_MAX];			// キーボードの押下状態を保持するワーク
	BYTE	m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー状態を保持するワーク
	BYTE	m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース状態を保持するワーク
	BYTE	m_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート状態を保持するワーク
	int		m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

	static Keyboard* mInstance;
};

#endif	