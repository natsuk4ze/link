//=====================================
//
//ゲームパッド処理[Gamepad.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Gamepad.h"
#include "../Tool/DebugWindow.h"

namespace GamePad
{
	/**************************************
	マクロ定義
	***************************************/
	#define DEADZONE		5000			// 各軸の25%を無効ゾーンとする
	#define RANGE_MAX		1000			// 有効範囲の最大値
	#define RANGE_MIN		-1000			// 有効範囲の最小値

	#define INPUT_SHORTWAIT (6)

	/**************************************
	グローバル変数
	***************************************/
	static LPDIRECTINPUT8 pInput = NULL;
	static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// パッドデバイス
	static int		padCount;			// 検出したパッドの数

	//スティックのRepeat状態検出用
	static int		padAxisXRepeat[GAMEPADMAX];
	static int		padAxisYRepeat[GAMEPADMAX];
	static int		lastAxisX[GAMEPADMAX];
	static int		lastAxisY[GAMEPADMAX];
	static int		axisXRepeatCnt[GAMEPADMAX];
	static int		axisYRepeatCnt[GAMEPADMAX];

	static float	padAxislRx[GAMEPADMAX];
	static float	padAxislRy[GAMEPADMAX];

	static DWORD	padState[GAMEPADMAX];	// パッド情報（複数対応）
	static DWORD	padTrigger[GAMEPADMAX];
	static DWORD	padRelease[GAMEPADMAX];
	static DWORD	padRepeat[GAMEPADMAX];
	static int		padRepeatCnt[GAMEPADMAX][PADBUTTON_MAX];

	static DWORD	povState[GAMEPADMAX];
	static DWORD	povTrigger[GAMEPADMAX];
	static DWORD	povRelease[GAMEPADMAX];
	static DWORD	povRepeat[GAMEPADMAX];
	static int	povRepeatCnt[GAMEPADMAX][POV_MAX];

	/**************************************
	パッド検査コールバック
	***************************************/
	BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
	{
		HRESULT result;

		result = pInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
		return DIENUM_CONTINUE;	// 次のデバイスを列挙
	}

	/**************************************
	初期化処理
	***************************************/
	HRESULT Init(LPDIRECTINPUT8 inputInterface)			// パッド初期化
	{
		HRESULT		result;
		int			i;

		padCount = 0;

		for (i = 0; i < GAMEPADMAX; i++)
		{
			padState[i] = 0x00000000l;	// 初期化
			padTrigger[i] = 0x00000000l;	// 初期化
			padRelease[i] = 0x00000000l;	// 初期化
		}

		// ジョイパッドを探す
		pInput = inputInterface;
		inputInterface->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchPadCallback, NULL, DIEDFL_ATTACHEDONLY);
		// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

		for (i = 0; i < padCount; i++) {
			// ジョイスティック用のデータ・フォーマットを設定
			result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
			if (FAILED(result))
				return false; // データフォーマットの設定に失敗

		  // モードを設定（フォアグラウンド＆非排他モード）
		  //		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		  //		if ( FAILED(result) )
		  //			return false; // モードの設定に失敗

		  // 軸の値の範囲を設定
		  // X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
		  // (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
		  // 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
			DIPROPRANGE				diprg;
			ZeroMemory(&diprg, sizeof(diprg));
			diprg.diph.dwSize = sizeof(diprg);
			diprg.diph.dwHeaderSize = sizeof(diprg.diph);
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin = RANGE_MIN;
			diprg.lMax = RANGE_MAX;
			// X軸の範囲を設定
			diprg.diph.dwObj = DIJOFS_X;
			pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
			// Y軸の範囲を設定
			diprg.diph.dwObj = DIJOFS_Y;
			pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

			// 各軸ごとに、無効のゾーン値を設定する。
			// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
			// 指定する値は、10000に対する相対値(2000なら20パーセント)。
			DIPROPDWORD				dipdw;
			dipdw.diph.dwSize = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
			dipdw.diph.dwHow = DIPH_BYOFFSET;
			dipdw.dwData = DEADZONE;
			//X軸の無効ゾーンを設定
			dipdw.diph.dwObj = DIJOFS_X;
			pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
			//Y軸の無効ゾーンを設定
			dipdw.diph.dwObj = DIJOFS_Y;
			pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

			//ジョイスティック入力制御開始
			pGamePad[i]->Acquire();
		}

		return true;

	}

	/**************************************
	終了処理
	***************************************/
	void Uninit()
	{
		for (int i = 0; i < GAMEPADMAX; i++) {
			if (pGamePad[i])
			{
				pGamePad[i]->Unacquire();
				pGamePad[i]->Release();
			}
		}
	}

	/**************************************
	更新処理
	***************************************/
	void Update(void)
	{
		HRESULT			result;
		DIJOYSTATE2		dijs;
		int				i;

		for (i = 0; i < padCount; i++)
		{
			DWORD lastPadState;
			lastPadState = padState[i];
			padState[i] = 0x00000000l;	// 初期化

			result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
			if (FAILED(result)) {
				result = pGamePad[i]->Acquire();
				while (result == DIERR_INPUTLOST)
					result = pGamePad[i]->Acquire();
			}

			result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
				result = pGamePad[i]->Acquire();
				while (result == DIERR_INPUTLOST)
					result = pGamePad[i]->Acquire();
			}

			if (dijs.lZ != 0 && dijs.lRx != 0)
			{
				padAxislRx[i] = (float)(dijs.lRx);
				padAxislRy[i] = (float)(dijs.lRy);

			}
			else
			{
				padAxislRx[i] = (float)(dijs.lZ + dijs.lRx);
				padAxislRy[i] = (float)(dijs.lRz + dijs.lRy);

			}

			// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
			//* y-axis (forward)
			if (dijs.lY < 0)
				padState[i] |= BUTTON_UP;
			//* y-axis (backward)
			if (dijs.lY > 0)
				padState[i] |= BUTTON_DOWN;
			//* x-axis (left)
			if (dijs.lX < 0)
				padState[i] |= BUTTON_LEFT;
			//* x-axis (right)
			if (dijs.lX > 0)
				padState[i] |= BUTTON_RIGHT;
			//* Ａボタン
			if (dijs.rgbButtons[0] & 0x80)
				padState[i] |= BUTTON_A;
			//* Ｂボタン
			if (dijs.rgbButtons[1] & 0x80)
				padState[i] |= BUTTON_B;
			//* Ｃボタン
			if (dijs.rgbButtons[2] & 0x80)
				padState[i] |= BUTTON_C;
			//* Ｘボタン
			if (dijs.rgbButtons[3] & 0x80)
				padState[i] |= BUTTON_X;
			//* Ｙボタン
			if (dijs.rgbButtons[4] & 0x80)
				padState[i] |= BUTTON_Y;
			//* Ｚボタン
			if (dijs.rgbButtons[5] & 0x80)
				padState[i] |= BUTTON_Z;
			//* Ｌボタン
			if (dijs.rgbButtons[6] & 0x80)
				padState[i] |= BUTTON_L;
			//* Ｒボタン
			if (dijs.rgbButtons[7] & 0x80)
				padState[i] |= BUTTON_R;
			//* ＳＴＡＲＴボタン
			if (dijs.rgbButtons[8] & 0x80)
				padState[i] |= BUTTON_START;
			//* Ｍボタン
			if (dijs.rgbButtons[9] & 0x80)
				padState[i] |= BUTTON_M;

			// Trigger設定
			padTrigger[i] = ((lastPadState ^ padState[i])	// 前回と違っていて
				& padState[i]);					// しかも今ONのやつ

												// Release設定
			padRelease[i] = ((lastPadState ^ padState[i]))	//前回と違っていて
				& (~padState[i]);				//今OFFのやつ

			// Repeat設定
			memcpy(&padRepeat[i], &padTrigger[i], sizeof(DWORD));
			for (DWORD button = BUTTON_UP; button <= BUTTON_M; button = button << 1)
			{
				int buttonID = GetButtonID(button);
				if (GetPress(i, button))
				{
					padRepeatCnt[i][buttonID]++;

					if (padRepeatCnt[i][buttonID] >= 20 && padRepeatCnt[i][buttonID] % 5 == 0)
					{
						padRepeat[i] |= button;
					}
				}
				else
				{
					padRepeat[i] &= ~button;
					padRepeatCnt[i][buttonID] = 0;
				}
			}

			//POV設定
			DWORD lastPovState = povState[i];
			ZeroMemory(&povState[i], sizeof(DWORD));

			//入力
			if (dijs.rgdwPOV[0] != -1)
			{
				povState[i] = 1 << (dijs.rgdwPOV[0] / 4500);
			}

			//Trigger & Release設定
			povTrigger[i] = ((lastPovState ^ povState[i]) & povState[i]);
			povRelease[i] = ((lastPovState ^ povState[i]) & (~povState[i]));

			//Repeat設定
			memcpy(&povRepeat[i], &povTrigger[i], sizeof(DWORD));
			for (DWORD pov = POV_UP; pov <= POV_LEFTUP; pov = pov << 1)
			{
				int povID = GetButtonID(pov);
				if (GetPressPOV(i, pov))
				{
					povRepeatCnt[i][povID]++;

					if (povRepeatCnt[i][povID] >= 20 && povRepeatCnt[i][povID] % 5 == 0)
					{
						povRepeat[i] |= pov;
					}
				}
				else
				{
					povRepeat[i] &= ~pov;
					povRepeatCnt[i][povID] = 0;
				}
			}
		}

	}

	/**************************************
	プレス検出処理
	***************************************/
	BOOL GetPress(int padNo, DWORD button)
	{
		return (button & padState[padNo]);
	}

	/**************************************
	リピート検出処理
	***************************************/
	BOOL GetRepeat(int padNo, DWORD button)
	{
		return (button & padRepeat[padNo]);
	}

	/**************************************
	トリガー検出処理
	***************************************/
	BOOL GetTrigger(int padNo, DWORD button)
	{
		return (button & padTrigger[padNo]);
	}

	/**************************************
	リリース検出処理
	***************************************/
	BOOL GetRelease(int padNo, DWORD button)
	{
		return (button & padRelease[padNo]);
	}

	/**************************************
	ハットスイッチプレス検出処理
	***************************************/
	BOOL GetPressPOV(int padNo, DWORD button)
	{
		return (button & povState[padNo]);
	}

	/**************************************
	ハットスイッチリピート検出処理
	***************************************/
	BOOL GetRepeatPOV(int padNo, DWORD button)
	{
		return (button & povRepeat[padNo]);
	}

	/**************************************
	ハットスイッチトリガー検出処理
	***************************************/
	BOOL GetTriggerPOV(int padNo, DWORD button)
	{
		return (button & povTrigger[padNo]);
	}

	/**************************************
	ハットスイッチリリース検出処理
	***************************************/
	BOOL GetReleasePOV(int padNo, DWORD button)
	{
		return (button & povRelease[padNo]);
	}

	/**************************************
	右プレス検出処理
	***************************************/
	BOOL GetPressLeft(int padNo)
	{
		return GetPress(padNo, BUTTON_LEFT) || GetPressPOV(padNo, POV_LEFT) || GetPressPOV(padNo, POV_LEFTUP) || GetPressPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	右プレス検出処理
	***************************************/
	BOOL GetPressRight(int padNo)
	{
		return GetPress(padNo, BUTTON_RIGHT) || GetPressPOV(padNo, POV_RIGHT) || GetPressPOV(padNo, POV_RIGHTUP) || GetPressPOV(padNo, POV_RIGHTDOWN);
	}

	/**************************************
	左リピート検出処理
	***************************************/
	BOOL GetRepeatLeft(int padNo)
	{
		return GetRepeat(padNo, BUTTON_LEFT) || GetRepeatPOV(padNo, POV_LEFT) || GetRepeatPOV(padNo, POV_LEFTUP) || GetRepeatPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	右リピート検出処理
	***************************************/
	BOOL GetRepeatRight(int padNo)
	{
		return GetRepeat(padNo, BUTTON_RIGHT) || GetRepeatPOV(padNo, POV_RIGHT) || GetRepeatPOV(padNo, POV_RIGHTUP) || GetRepeatPOV(padNo, POV_RIGHTDOWN);
	}

	/**************************************
	左トリガー検出処理
	***************************************/
	BOOL GetTriggerLeft(int padNo)
	{
		return GetTrigger(padNo, BUTTON_LEFT) || GetTriggerPOV(padNo, POV_LEFT) || GetTriggerPOV(padNo, POV_LEFTUP) || GetTriggerPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	右トリガー検出処理
	***************************************/
	BOOL GetTriggerRight(int padNo)
	{
		return GetTrigger(padNo, BUTTON_RIGHT) || GetTriggerPOV(padNo, POV_RIGHT) || GetTriggerPOV(padNo, POV_RIGHTUP) || GetTriggerPOV(padNo, POV_RIGHTDOWN);
	}

	/**************************************
	下プレス検出処理
	***************************************/
	BOOL GetPressDown(int padNo)
	{
		return GetPress(padNo, BUTTON_DOWN) || GetPressPOV(padNo, POV_DOWN) || GetPressPOV(padNo, POV_RIGHTDOWN) || GetPressPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	上プレス検出処理
	***************************************/
	BOOL GetPressUp(int padNo)
	{
		return GetPress(padNo, BUTTON_UP) || GetPressPOV(padNo, POV_UP) || GetPressPOV(padNo, POV_RIGHTUP) || GetPressPOV(padNo, POV_LEFTUP);
	}

	/**************************************
	下リピート検出処理
	***************************************/
	BOOL GetRepeatDown(int padNo)
	{
		return GetRepeat(padNo, BUTTON_DOWN) || GetRepeatPOV(padNo, POV_DOWN) || GetRepeatPOV(padNo, POV_RIGHTDOWN) || GetRepeatPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	上リピート検出処理
	***************************************/
	BOOL GetRepeatUp(int padNo)
	{
		return GetRepeat(padNo, BUTTON_UP) || GetRepeatPOV(padNo, POV_UP) || GetRepeatPOV(padNo, POV_RIGHTUP) || GetRepeatPOV(padNo, POV_LEFTUP);
	}

	/**************************************
	下トリガー検出処理
	***************************************/
	BOOL GetTriggerDown(int padNo)
	{
		return GetTrigger(padNo, BUTTON_DOWN) || GetTriggerPOV(padNo, POV_DOWN) || GetTriggerPOV(padNo, POV_RIGHTDOWN) || GetTriggerPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	上トリガー検出処理
	***************************************/
	BOOL GetTriggerUp(int padNo)
	{
		return GetTrigger(padNo, BUTTON_UP) || GetTriggerPOV(padNo, POV_UP) || GetTriggerPOV(padNo, POV_RIGHTUP) || GetTriggerPOV(padNo, POV_LEFTUP);
	}

	/**************************************
	X軸トリガー検出処理
	***************************************/
	int GetTriggerX(int padNo)
	{
		if (GetTrigger(padNo, BUTTON_RIGHT))
			return 1;

		else if (GetTrigger(padNo, BUTTON_LEFT))
			return -1;

		else
			return 0;
	}

	/**************************************
	Y軸トリガー検出処理
	***************************************/
	int GetTriggerY(int padNo)
	{
		if (GetTrigger(padNo, BUTTON_UP))
			return 1;

		else if (GetTrigger(padNo, BUTTON_DOWN))
			return -1;

		else
			return 0;
	}

	/**************************************
	パッド数を返す処理
	***************************************/
	int GetPadCount(void)
	{
		return padCount;
	}

	/**************************************
	ボタンID取得処理
	***************************************/
	int GetButtonID(DWORD button)
	{
		int id = 0;
		for (DWORD bit = button; bit > 0x01; bit = bit >> 1)
		{
			id++;
		}

		return id;
	}

	/**************************************
	右スティックX軸入力計算処理
	***************************************/
	float GetRightStickX(int padNo)
	{
		if (padNo >= padCount)
		{
			return 0.0f;
		}

		return (padAxislRx[padNo] / 65535.0f) - 0.5f;
	}

	/**************************************
	右スティックY軸入力計算処理
	***************************************/
	float GetRightStickY(int padNo)
	{
		if (padNo >= padCount)
		{
			return 0.0f;
		}


		return (padAxislRy[padNo] / 65535.0f) - 0.5f;
	}
}

