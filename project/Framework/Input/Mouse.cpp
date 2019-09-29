//=====================================
//
//マウス処理[Mouse.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Mouse.h"

/**************************************
マクロ定義
***************************************/

/**************************************
グローバル変数
***************************************/
Mouse* Mouse::mInstance = NULL;

/**************************************
コンストラクタ
***************************************/
Mouse::Mouse()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

/**************************************
初期化処理
***************************************/
HRESULT Mouse::Init(HINSTANCE hInst, HWND hWindow, LPDIRECTINPUT8 inputInterface)
{
	HRESULT result;
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
Mouse::~Mouse()
{
	if (pMouse)
	{
		pMouse->Unacquire();
		pMouse->Release();
		pMouse = NULL;
	}

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

/**************************************
更新処理
***************************************/
HRESULT Mouse::Update()
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
		for (int i = 0; i<8; i++)
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
D3DXVECTOR3 Mouse::GetMousePosition(HWND hWnd)
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
BOOL Mouse::GetPressLeft(void)
{
	return (BOOL)(mInstance->mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
}
BOOL Mouse::GetTriggerLeft(void)
{
	return (BOOL)(mInstance->mouseTrigger.rgbButtons[0] & 0x80);
}
BOOL Mouse::GetPressRight(void)
{
	return (BOOL)(mInstance->mouseState.rgbButtons[1] & 0x80);
}
BOOL Mouse::GetTriggerRight(void)
{
	return (BOOL)(mInstance->mouseTrigger.rgbButtons[1] & 0x80);
}
BOOL Mouse::GetPressCenter(void)
{
	return (BOOL)(mInstance->mouseState.rgbButtons[2] & 0x80);
}
BOOL Mouse::GetTriggerCenter(void)
{
	return (BOOL)(mInstance->mouseTrigger.rgbButtons[2] & 0x80);
}

/**************************************
マウス座標取得処理
***************************************/
float Mouse::GetX(void)
{
	return float(mInstance->mouseState.lX);
}
float Mouse::GetY(void)
{
	return float(mInstance->mouseState.lY);
}
float Mouse::GetZ(void)
{
	return float(mInstance->mouseState.lZ);
}
