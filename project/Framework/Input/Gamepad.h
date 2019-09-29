//=====================================
//
//ゲームパッドヘッダ[Gamepad.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "../../main.h"

/**************************************
マクロ定義
***************************************/
#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)
#define BUTTON_A		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット
#define PADBUTTON_MAX	14			// 入力に使えるボタンの最大数

/**************************************
クラス定義
***************************************/
class GamePad
{
public:
	GamePad();
	~GamePad(); 
	HRESULT Init(LPDIRECTINPUT8 pInput);

	void Update();

	static BOOL GetPress(int padNo, DWORD button);
	static BOOL GetTrigger(int padNo, DWORD button);
	static BOOL GetRelease(int padNo, DWORD button);

	static float GetRightStickX(int padNo);
	static float GetRightStickY(int padNo);

	static int GetTriggerX(int padNo);
	static int GetTriggerY(int padNo);

	static int GetPadCount();

private:
	//スティックのRepeat状態検出用
	int		padAxisXRepeat[GAMEPADMAX];
	int		padAxisYRepeat[GAMEPADMAX];
	int		lastAxisX[GAMEPADMAX];
	int		lastAxisY[GAMEPADMAX];
	int		axisXRepeatCnt[GAMEPADMAX];
	int		axisYRepeatCnt[GAMEPADMAX];

	float	padAxislRx[GAMEPADMAX];
	float	padAxislRy[GAMEPADMAX];

	LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// パッドデバイス

	DWORD	padState[GAMEPADMAX];	// パッド情報（複数対応）
	DWORD	padTrigger[GAMEPADMAX];
	DWORD	padRelease[GAMEPADMAX];
	int		padCount;			// 検出したパッドの数

	static GamePad* mInstance;
};

#endif