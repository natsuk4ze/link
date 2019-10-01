//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// staticメンバ
//*****************************************************************************
#undef new
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Input::Input()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}

	pad = new GamePad();
	keyboard = new Keyboard();
	mouse = new Mouse();
}

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT Input::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	//if(!pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&pDInput, NULL);
	}

	// キーボードの初期化
	keyboard->Init(hInst, hWnd, pDInput);

	//マウス初期化
	mouse->Init(hInst, hWnd, pDInput);

	//パッド初期化処理
	pad->Init(pDInput);

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
Input::~Input()
{
	// キーボードの終了処理
	SAFE_DELETE(keyboard);

	//マウス終了処理
	SAFE_DELETE(mouse);

	//パッド終了処理
	SAFE_DELETE(pad);

	if(pDInput)
	{// DirectInputオブジェクトの開放
		pDInput->Release();
		pDInput = NULL;
	}

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void Input::Update(void)
{
	// キーボードの更新
	keyboard->Update();

	//マウス更新処理
	mouse->Update();

	//ゲームパッド更新処理
	pad->Update();
}

//=============================================================================
// 水平方向への入力処理
//=============================================================================
float Input::GetPressHorizontail(int no)
{
	if (no == 0)
	{
		if (Keyboard::GetPress(DIK_LEFT) || GamePad::GetPress(0, BUTTON_LEFT))
			return -1.0f;

		if (Keyboard::GetPress(DIK_RIGHT) || GamePad::GetPress(0, BUTTON_RIGHT))
			return 1.0f;

		return 0.0f;
	}

	if (GamePad::GetPress(no, BUTTON_LEFT))
		return -1.0f;

	if (GamePad::GetPress(no, BUTTON_RIGHT))
		return 1.0f;

	return 0.0f;
}

//=============================================================================
// 垂直方向への入力処理
//=============================================================================
float Input::GetPressVertical(int no)
{
	if (no == 0)
	{
		if (Keyboard::GetPress(DIK_DOWN) || GamePad::GetPress(0, BUTTON_DOWN))
			return -1.0f;

		if (Keyboard::GetPress(DIK_UP) || GamePad::GetPress(0, BUTTON_UP))
			return 1.0f;

		return 0.0f;
	}

	if (GamePad::GetPress(no, BUTTON_DOWN))
		return -1.0f;

	if (GamePad::GetPress(no, BUTTON_UP))
		return 1.0f;

	return 0.0f;
}

//=============================================================================
// 垂直方向への入力処理
//=============================================================================
float Input::GetRepeatHorizontal(int no)
{
	//TODO:ゲームパッドもリピート入力に対応
	if (no == 0)
	{
		if (Keyboard::GetRepeat(DIK_LEFT))
			return -1.0f;

		if (Keyboard::GetRepeat(DIK_RIGHT))
			return 1.0f;

		return 0.0f;
	}

	return 0.0f;
}

//=============================================================================
// 垂直方向への入力処理
//=============================================================================
float Input::GetRepeatVertical(int no)
{
	//TODO:ゲームパッドもリピート入力に対応
	if (no == 0)
	{
		if (Keyboard::GetRepeat(DIK_DOWN))
			return -1.0f;

		if (Keyboard::GetRepeat(DIK_UP))
			return 1.0f;

		return 0.0f;
	}

	return 0.0f;
}
