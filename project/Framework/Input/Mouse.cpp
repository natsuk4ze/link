//=====================================
//
//マウス処理[Mouse.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Mouse.h"

namespace Mouse
{
	/**************************************
	グローバル変数
	***************************************/
	static LPDIRECTINPUTDEVICE8 pMouse = NULL; // mouse

	static DIMOUSESTATE2   mouseState;		// マウスのダイレクトな状態
	static DIMOUSESTATE2   mouseTrigger;	// 押された瞬間だけON

	static HWND hWnd;

	/**************************************
	初期化処理
	***************************************/
	HRESULT Init(HINSTANCE hInst, HWND hWindow, LPDIRECTINPUT8 inputInterface)
	{
		HRESULT result;

		hWnd = hWindow;

		// デバイス作成
		result = inputInterface->CreateDevice(GUID_SysMouse, &pMouse, NULL);
		if (FAILED(result) || pMouse == NULL)
		{
			MessageBox(hWindow, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}
		// データフォーマット設定
		result = pMouse->SetDataFormat(&c_dfDIMouse2);
		if (FAILED(result))
		{
			MessageBox(hWindow, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}
		// 他のアプリと協調モードに設定
		result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(result))
		{
			MessageBox(hWindow, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}

		// デバイスの設定
		DIPROPDWORD prop;

		prop.diph.dwSize = sizeof(prop);
		prop.diph.dwHeaderSize = sizeof(prop.diph);
		prop.diph.dwObj = 0;
		prop.diph.dwHow = DIPH_DEVICE;
		prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

		result = pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
		if (FAILED(result))
		{
			MessageBox(hWindow, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
			return result;
		}

		// アクセス権を得る
		pMouse->Acquire();
		return result;
	}

	/**************************************
	終了処理
	***************************************/
	void Uninit()
	{
		if (pMouse)
		{
			pMouse->Unacquire();
			pMouse->Release();
			pMouse = NULL;
		}
	}

	/**************************************
	更新処理
	***************************************/
	HRESULT Update()
	{
		HRESULT result;
		// 前回の値保存
		DIMOUSESTATE2 lastMouseState = mouseState;
		// データ取得
		result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
		if (SUCCEEDED(result))
		{
			mouseTrigger.lX = mouseState.lX;
			mouseTrigger.lY = mouseState.lY;
			mouseTrigger.lZ = mouseState.lZ;
			// マウスのボタン状態
			for (int i = 0; i < 8; i++)
			{
				mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
					mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
			}
		}
		else	// 取得失敗
		{
			// アクセス権を得てみる
			result = pMouse->Acquire();
		}

		return result;

	}

	/**************************************
	マウス座標取得処理
	***************************************/
	D3DXVECTOR3 GetMousePosition()
	{
		POINT position;

		if (GetCursorPos(&position))
		{
			ScreenToClient(hWnd, &position);

			if (position.x < 0)
			{
				position.x = 0;
			}
			else if (position.x > SCREEN_WIDTH)
			{
				position.x = SCREEN_WIDTH;
			}

			if (position.y < 0)
			{
				position.y = 0;
			}
			else if (position.y > SCREEN_HEIGHT)
			{
				position.y = SCREEN_HEIGHT;
			}

			return D3DXVECTOR3((float)position.x, (float)position.y, 0.0f);
		}
		else
		{
			return D3DXVECTOR3(0, 0, 0);
		}
	}

	/**************************************
	マウス入力検出処理
	***************************************/
	BOOL GetPressLeft(void)
	{
		return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
	}
	BOOL GetTriggerLeft(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
	}
	BOOL GetPressRight(void)
	{
		return (BOOL)(mouseState.rgbButtons[1] & 0x80);
	}
	BOOL GetTriggerRight(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
	}
	BOOL GetPressCenter(void)
	{
		return (BOOL)(mouseState.rgbButtons[2] & 0x80);
	}
	BOOL GetTriggerCenter(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
	}

	/**************************************
	マウス座標取得処理
	***************************************/
	float GetX(void)
	{
		return float(mouseState.lX);
	}
	float GetY(void)
	{
		return float(mouseState.lY);
	}
	float GetZ(void)
	{
		return float(mouseState.lZ);
	}
}