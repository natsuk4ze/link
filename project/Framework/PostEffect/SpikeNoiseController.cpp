//=====================================
//
//スパイクノイズコントローラ処理[SpikeNoiseController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpikeNoiseController.h"
#include "Effect\SpikeNoise.h"
#include "../Math/Easing.h"

/**************************************
マクロ定義
***************************************/
#define USE_SPIKENOISECTRL_DEBUG

#define SPIKENOISE_SCROLL_SPEED	(0.001f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
セット処理
***************************************/
void SpikeNoiseController::SetNoise(float power, int effectTime)
{
	if (active)
		return;

	this->active = true;
	this->cntFrame = 0;
	this->effectTime = effectTime;
	this->state = State::Start;
	this->destPower = power;
	this->srcPower = 0.0f;
	this->base = 0.0f;
}

/**************************************
更新処理
***************************************/
void SpikeNoiseController::Update()
{
	if (!active)
		return;

	cntFrame++;

	//ノイズをスクロール
	base = Math::WrapAround(0.0f, 1.0f, base + SPIKENOISE_SCROLL_SPEED);
	spikeNoise->SetBaseY(base);

	//各ステート更新処理
	if (state == State::Start)
		OnStart();
	else if (state == State::Wait)
		OnWait();
	else
		OnEnd();

	//ドローフラグを立てる
	this->drawFlag = true;
}

/**************************************
Start更新処理
***************************************/
void SpikeNoiseController::OnStart()
{
	const int Duration = 10;

	//ノイズの強さをアニメーション
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, this->srcPower, this->destPower, EaseType::InCubic);
	this->spikeNoise->SetLength(power);

	//遷移判定
	if (cntFrame == Duration)
	{
		state++;
		this->cntFrame = 0;
	}
}

/**************************************
Wait更新処理
***************************************/
void SpikeNoiseController::OnWait()
{
	//遷移判定
	if (cntFrame == effectTime)
	{
		state++;
		this->cntFrame = 0;
		srcPower = destPower;
		destPower = 0.0f;
	}
}

/**************************************
End更新処理
***************************************/
void SpikeNoiseController::OnEnd()
{
	const int Duration = 10;

	//ノイズの強さをアニメーション
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, this->srcPower, this->destPower, OutCubic);
	this->spikeNoise->SetLength(power);

	//遷移判定
	if (cntFrame == Duration)
	{
		active = false;
	}
}

/**************************************
描画処理
***************************************/
void SpikeNoiseController::Draw(LPDIRECT3DTEXTURE9 targetTexture)
{
	//非アクティブであれば早期リターン
	if (!this->active)
		return;

	//描画済みであれば早期リターン
	if (!this->drawFlag)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, surface);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	pDevice->SetTexture(0, defaultTarget);
	spikeNoise->DrawEffect();

	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	pDevice->SetTexture(0, texture);
	spikeNoise->Draw();

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

/**************************************
コンストラクタ
***************************************/
SpikeNoiseController::SpikeNoiseController()
{
	//スパイクノイズのインスタンスを生成
	spikeNoise = new SpikeNoise();

	//テクスチャを作成しサーフェイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	texture->GetSurfaceLevel(0, &surface);
}

/**************************************
デストラクタ
***************************************/
SpikeNoiseController::~SpikeNoiseController()
{
	//解放
	delete spikeNoise;
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}