//=====================================
//
//ショックブラーコントローラ処理[ShockBlurController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ShockBlurController.h"
#include "../Math/Easing.h"

/**************************************
マクロ定義
***************************************/
#define SHOCKBLURCTRL_USE_DEBUG

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
更新処理
***************************************/
void ShockBlurController::Update()
{
	//非アクティブであれば早期リターン
	if (!active)
		return;

	cntFrame++;

	//各ステート更新処理
	if (state == State::Start)
		OnStart();
	else if (state == State::Wait)
		OnWait();
	else
		OnEnd();

	//ドローフラグを立てる
	drawFlag = true;
}

/**************************************
Start更新処理
***************************************/
void ShockBlurController::OnStart()
{
	const int Duration = 10;

	//ブラーの強さをアニメーション
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, srcPower, destPower, EaseType::InCubic);

	if (cntFrame == Duration)
	{
		cntFrame = 0;
		state++;
	}
}

/**************************************
Wait更新処理
***************************************/
void ShockBlurController::OnWait()
{
	//待機のみ

	if (cntFrame == effectTime)
	{
		cntFrame = 0;
		srcPower = destPower;
		destPower = 0.0f;
		state++;
	}
}

/**************************************
End更新処理
***************************************/
void ShockBlurController::OnEnd()
{
	const int Duration = 10;

	//ブラーの強さをアニメーション
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, srcPower, destPower, EaseType::OutCubic);

	if (cntFrame == Duration)
	{
		cntFrame = 0;
		active = false;
	}
}

/**************************************
描画処理
***************************************/
void ShockBlurController::Draw(LPDIRECT3DTEXTURE9 targetTexture)
{
	//非アクティブであれば早期リターン
	if (!active)
		return;

	//描画済みであれば早期リターン
	if (!drawFlag)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, surface);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	pDevice->SetTexture(0, defaultTarget);
	shockBlur->DrawEffect();

	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	pDevice->SetTexture(0, texture);
	shockBlur->Draw();

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
エフェクトセット処理
***************************************/
void ShockBlurController::SetBlur(D3DXVECTOR3 pos, float power, int duration)
{
	//アクティブである場合は上書きしない
	if (active)
		return;

	active = true;
	srcPower = 0.0f;
	destPower = power;
	cntFrame = 0;
	state = State::Start;
	effectTime = duration;

	shockBlur->SetCenterPos(pos);
}

/*************************************
コンストラクタ
***************************************/
ShockBlurController::ShockBlurController()
{
	shockBlur = new ShockBlur();
	shockBlur->SetSurfaceSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	texture->GetSurfaceLevel(0, &surface);
}

/**************************************
デストラクタ
***************************************/
ShockBlurController::~ShockBlurController()
{
	delete shockBlur;
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}