//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

namespace Input
{
	//*****************************************************************************
	// グローバル変数
	//*****************************************************************************
	LPDIRECTINPUT8 pDInput = NULL;					// IDirectInput8インターフェースへのポインタ

	//=============================================================================
	// 入力処理の初期化
	//=============================================================================
	HRESULT Init(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		if(!pDInput)
		{
			// DirectInputオブジェクトの作成
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)&pDInput, NULL);
		}

		// キーボードの初期化
		Keyboard::Init(hInst, hWnd, pDInput);

		//マウス初期化
		Mouse::Init(hInst, hWnd, pDInput);

		//パッド初期化処理
		GamePad::Init(pDInput);

		return S_OK;
	}

	//=============================================================================
	// 入力処理の終了処理
	//=============================================================================
	void Uninit()
	{
		// キーボードの終了処理
		Keyboard::Uninit();

		//マウス終了処理
		Mouse::Uninit();

		//パッド終了処理
		GamePad::Uninit();

		if (pDInput)
		{// DirectInputオブジェクトの開放
			pDInput->Release();
			pDInput = NULL;
		}
	}

	//=============================================================================
	// 入力処理の更新処理
	//=============================================================================
	void Update(void)
	{
		// キーボードの更新
		Keyboard::Update();

		//マウス更新処理
		Mouse::Update();

		//ゲームパッド更新処理
		GamePad::Update();
	}

	//=============================================================================
	// 水平方向への入力処理
	//=============================================================================
	float GetPressHorizontail(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_LEFT) || GamePad::GetPress(0, BUTTON_LEFT) || GamePad::GetPressPOV(0, POV_LEFT))
				return -1.0f;

			if (Keyboard::GetPress(DIK_RIGHT) || GamePad::GetPress(0, BUTTON_RIGHT) || GamePad::GetPressPOV(0, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPress(no, BUTTON_LEFT) || GamePad::GetPressPOV(no, POV_LEFT))
				return -1.0f;

			if (GamePad::GetPress(no, BUTTON_RIGHT) || GamePad::GetPressPOV(no, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}
	}

	//=============================================================================
	// 垂直方向への入力処理
	//=============================================================================
	float GetPressVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_DOWN) || GamePad::GetPress(0, BUTTON_DOWN) || GamePad::GetPressPOV(0, POV_DOWN))
				return -1.0f;

			if (Keyboard::GetPress(DIK_UP) || GamePad::GetPress(0, BUTTON_UP) || GamePad::GetPressPOV(0, POV_UP))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPress(no, BUTTON_DOWN) || GamePad::GetPress(no, POV_DOWN))
				return -1.0f;

			if (GamePad::GetPress(no, BUTTON_UP) || GamePad::GetPress(no, POV_UP))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// 水平方向への入力処理
	//=============================================================================
	float GetTriggerHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetTrigger(DIK_LEFT) || GamePad::GetTrigger(0, BUTTON_LEFT) || GamePad::GetTriggerPOV(0, POV_LEFT))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_RIGHT) || GamePad::GetTrigger(0, BUTTON_RIGHT) || GamePad::GetTriggerPOV(0, POV_RIGHT))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTrigger(no, BUTTON_LEFT) || GamePad::GetTriggerPOV(no, POV_LEFT))
				return -1.0f;

			if (GamePad::GetTrigger(no, BUTTON_RIGHT) || GamePad::GetTriggerPOV(no, POV_RIGHT))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// 垂直方向への入力処理
	//=============================================================================
	float GetTriggerVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetTrigger(DIK_DOWN) || GamePad::GetTrigger(0, BUTTON_DOWN) || GamePad::GetTriggerPOV(0, POV_DOWN))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_UP) || GamePad::GetTrigger(0, BUTTON_UP) || GamePad::GetTriggerPOV(0, POV_UP))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTrigger(no, BUTTON_DOWN) || GamePad::GetTriggerPOV(no, POV_DOWN))
				return -1.0f;

			if (GamePad::GetTrigger(no, BUTTON_UP) || GamePad::GetTriggerPOV(no, POV_UP))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// 垂直方向への入力処理
	//=============================================================================
	float GetRepeatHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_LEFT) || GamePad::GetRepeat(0, BUTTON_LEFT) || GamePad::GetRepeatPOV(0, POV_LEFT))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_RIGHT) || GamePad::GetRepeat(0, BUTTON_RIGHT) || GamePad::GetRepeatPOV(0, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeat(no, BUTTON_LEFT) || GamePad::GetRepeatPOV(no, POV_LEFT))
				return -1.0f;

			if (GamePad::GetRepeat(no, BUTTON_RIGHT) || GamePad::GetRepeatPOV(no, POV_RIGHT))
				return 1.0f;

			return 0.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// 垂直方向への入力処理
	//=============================================================================
	float GetRepeatVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_DOWN) || GamePad::GetRepeat(no, BUTTON_DOWN) || GamePad::GetRepeatPOV(no, POV_DOWN))
				return -1.0f;
			
			if (Keyboard::GetRepeat(DIK_UP) || GamePad::GetRepeat(no, BUTTON_UP) || GamePad::GetRepeatPOV(no, POV_UP))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeat(no, BUTTON_DOWN) || GamePad::GetRepeatPOV(no, POV_DOWN))
				return -1.0f;

			if (GamePad::GetRepeat(no, BUTTON_UP) || GamePad::GetRepeatPOV(no, POV_UP))
				return 1.0f;
		}

		return 0.0f;
	}
}