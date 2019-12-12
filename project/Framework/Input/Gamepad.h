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
#define BUTTON_A		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)、アケコンの☐ボタン
#define BUTTON_B		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)、アケコンの✖ボタン
#define BUTTON_C		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)、アケコンの〇ボタン
#define BUTTON_X		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)、アケコンの△ボタン
#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)、アケコンのL1ボタン
#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)、アケコンのR1ボタン
#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)、アケコンのShareボタン
#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)、アケコンのOptionsボタン
#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット
#define PADBUTTON_MAX	14			// 入力に使えるボタンの最大数

#define POV_UP			(0x0001)			//ハットスイッチの上
#define POV_RIGHTUP		(0x0002)			//ハットスイッチの右上
#define POV_RIGHT		(0x0004)			//ハットスイッチの右
#define POV_RIGHTDOWN	(0x0008)			//ハットスイッチの右下
#define POV_DOWN		(0x0010)			//ハットスイッチの下
#define POV_LEFTDOWN	(0x0020)			//ハットスイッチの左下
#define POV_LEFT		(0x0040)			//ハットスイッチの左
#define POV_LEFTUP		(0x0080)			//ハットスイッチの左上
#define POV_MAX			(8)

/**************************************
クラス定義
***************************************/
namespace GamePad
{
	HRESULT Init(LPDIRECTINPUT8 pInput);
	void Uninit();
	void Update();

	BOOL GetPress(int padNo, DWORD button);
	BOOL GetRepeat(int padNo, DWORD button);
	BOOL GetTrigger(int padNo, DWORD button);
	BOOL GetRelease(int padNo, DWORD button);

	BOOL GetPressPOV(int padNo, DWORD button);
	BOOL GetRepeatPOV(int padNo, DWORD button);
	BOOL GetTriggerPOV(int padNo, DWORD button);
	BOOL GetReleasePOV(int padNo, DWORD button);

	BOOL GetPressLeft(int padNo);
	BOOL GetPressRight(int padNo);
	BOOL GetRepeatLeft(int padNo);
	BOOL GetRepeatRight(int padNo);
	BOOL GetTriggerLeft(int padNo);
	BOOL GetTriggerRight(int padNo);

	BOOL GetPressDown(int padNo);
	BOOL GetPressUp(int padNo);
	BOOL GetRepeatDown(int padNo);
	BOOL GetRepeatUp(int padNo);
	BOOL GetTriggerDown(int padNo);
	BOOL GetTriggerUp(int padNo);

	float GetRightStickX(int padNo);
	float GetRightStickY(int padNo);

	int GetTriggerX(int padNo);
	int GetTriggerY(int padNo);

	int GetPadCount();

	int GetButtonID(DWORD button);
};

#endif