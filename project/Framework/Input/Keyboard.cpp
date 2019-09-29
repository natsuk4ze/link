//=====================================
//
//キーボード処理[Keyboard.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Keyboard.h"

//=============================================================================
// staticメンバ
//=============================================================================
Keyboard* Keyboard::mInstance = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
Keyboard::Keyboard()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

//=============================================================================
// キーボードの初期化処理
//=============================================================================
HRESULT Keyboard::Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 inputInterface)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = inputInterface->CreateDevice(GUID_SysKeyboard, &m_pDIDevKeyboard, NULL);
	if (FAILED(hr) || m_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
Keyboard::~Keyboard()
{
	if (m_pDIDevKeyboard)
	{// デバイスオブジェクトの開放
		m_pDIDevKeyboard->Release();
		m_pDIDevKeyboard = NULL;
	}

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void Keyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	hr = m_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState);
	if (SUCCEEDED(hr))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_aKeyStateRepeat[nCntKey] = m_aKeyStateTrigger[nCntKey];

			if (aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if (m_aKeyStateRepeatCnt[nCntKey] >= 20 && m_aKeyStateRepeatCnt[nCntKey] % 5 == 0)
				{
					m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}
				//else
				//{
				//	m_aKeyStateRepeat[nCntKey] = 0;
				//}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		m_pDIDevKeyboard->Acquire();
	}

	return;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool Keyboard::GetPress(int nKey)
{
	return (mInstance->m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool Keyboard::GetTrigger(int nKey)
{
	return (mInstance->m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool Keyboard::GetRepeat(int nKey)
{
	return (mInstance->m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool Keyboard::GetRelease(int nKey)
{
	return (mInstance->m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}