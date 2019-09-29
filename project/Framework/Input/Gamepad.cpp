//=====================================
//
//ゲームパッド処理[Gamepad.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Gamepad.h"

/**************************************
マクロ定義
***************************************/
#define DEADZONE		5000			// 各軸の25%を無効ゾーンとする
#define RANGE_MAX		1000			// 有効範囲の最大値
#define RANGE_MIN		-1000			// 有効範囲の最小値

#define INPUT_SHORTWAIT (6)

GamePad* GamePad::mInstance = NULL;
static LPDIRECTINPUT8 pInput = NULL;
LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// パッドデバイス
int		padCount;			// 検出したパッドの数

/*************************************
コンストラクタ
***************************************/
GamePad::GamePad()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

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
HRESULT GamePad::Init(LPDIRECTINPUT8 inputInterface)			// パッド初期化
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
GamePad::~GamePad()
{
	for (int i = 0; i < GAMEPADMAX; i++) {
		if (pGamePad[i])
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

/**************************************
更新処理
***************************************/
void GamePad::Update(void)
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

											//スティックのRepeat判定処理
		padAxisYRepeat[i] = GetTriggerY(i);

		if (BUTTON_UP & padState[i])
		{
			axisYRepeatCnt[i]++;
			if (axisYRepeatCnt[i] >= 20 && axisYRepeatCnt[i] % INPUT_SHORTWAIT == 0)
			{
				padAxisYRepeat[i] = 1;
			}
		}
		else if (BUTTON_DOWN & padState[i])
		{
			axisYRepeatCnt[i]++;
			if (axisYRepeatCnt[i] >= 20 && axisYRepeatCnt[i] % INPUT_SHORTWAIT == 0)
			{
				padAxisYRepeat[i] = -1;
			}
		}
		else
		{
			axisYRepeatCnt[i] = 0;
			padAxisYRepeat[i] = 0;
		}

		padAxisXRepeat[i] = GetTriggerX(i);

		if (BUTTON_RIGHT & padState[i])
		{
			axisXRepeatCnt[i]++;
			if (axisXRepeatCnt[i] >= 20 && axisXRepeatCnt[i] % INPUT_SHORTWAIT == 0)
			{
				padAxisXRepeat[i] = 1;
			}
		}
		else if (BUTTON_LEFT & padState[i])
		{
			axisXRepeatCnt[i]++;
			if (axisXRepeatCnt[i] >= 20 && axisXRepeatCnt[i] % INPUT_SHORTWAIT == 0)
			{
				padAxisXRepeat[i] = -1;
			}
		}
		else
		{
			axisXRepeatCnt[i] = 0;
			padAxisXRepeat[i] = 0;
		}

	}

}

/**************************************
プレス検出処理
***************************************/
BOOL GamePad::GetPress(int padNo, DWORD button)
{
	return (button & mInstance->padState[padNo]);
}

/**************************************
トリガー検出処理
***************************************/
BOOL GamePad::GetTrigger(int padNo, DWORD button)
{
	return (button & mInstance->padTrigger[padNo]);
}

/**************************************
リリース検出処理
***************************************/
BOOL GamePad::GetRelease(int padNo, DWORD button)
{
	return (button & mInstance->padRelease[padNo]);
}

/**************************************
X軸トリガー検出処理
***************************************/
int GamePad::GetTriggerX(int padNo)
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
int GamePad::GetTriggerY(int padNo)
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
int GamePad::GetPadCount(void)
{
	return mInstance->padCount;
}

/**************************************
右スティックX軸入力計算処理
***************************************/
float GamePad::GetRightStickX(int padNo)
{
	if (padNo >= mInstance->padCount)
	{
		return 0.0f;
	}

	return (mInstance->padAxislRx[padNo] / 65535.0f) - 0.5f;
}


/**************************************
右スティックY軸入力計算処理
***************************************/
float GamePad::GetRightStickY(int padNo)
{
	if (padNo >= mInstance->padCount)
	{
		return 0.0f;
	}


	return (mInstance->padAxislRy[padNo] / 65535.0f) - 0.5f;
}


