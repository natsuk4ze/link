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

		if (!pDInput)
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
			if (Keyboard::GetPress(DIK_LEFT) || GamePad::GetPressLeft(0))
				return -1.0f;

			if (Keyboard::GetPress(DIK_RIGHT) || GamePad::GetPressRight(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPressLeft(no))
				return -1.0f;

			if (GamePad::GetPressRight(no))
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
			if (Keyboard::GetPress(DIK_DOWN) || GamePad::GetPressDown(0))
				return -1.0f;

			if (Keyboard::GetPress(DIK_UP) || GamePad::GetPressUp(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPressDown(no))
				return -1.0f;

			if (GamePad::GetPressUp(no))
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
			if (Keyboard::GetTrigger(DIK_LEFT) || GamePad::GetTriggerLeft(0))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_RIGHT) || GamePad::GetTriggerRight(0))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTriggerLeft(no))
				return -1.0f;

			if (GamePad::GetTriggerRight(no))
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
			if (Keyboard::GetTrigger(DIK_DOWN) || GamePad::GetTriggerDown(0))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_UP) || GamePad::GetTriggerUp(0))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTriggerDown(no))
				return -1.0f;

			if (GamePad::GetTriggerUp(no))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// 水平方向への入力処理
	//=============================================================================
	float GetRepeatHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_LEFT) || GamePad::GetRepeatLeft(0))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_RIGHT) || GamePad::GetRepeatRight(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeatLeft(no))
				return -1.0f;

			if (GamePad::GetRepeatRight(no))
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
			if (Keyboard::GetRepeat(DIK_DOWN) || GamePad::GetRepeatDown(0))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_UP) || GamePad::GetRepeatUp(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeatDown(no))
				return -1.0f;

			if (GamePad::GetRepeatUp(no))
				return 1.0f;
		}

		return 0.0f;
	}
}