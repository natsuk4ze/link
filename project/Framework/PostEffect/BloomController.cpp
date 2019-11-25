//=====================================
//
//ブルームコントローラ処理[BloomController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloomController.h"
#include "Effect/BloomFilter.h"
#include "Effect/BlurFilter.h"

#include "../Tool/DebugWindow.h"

//#define DEBUG_BLOOM
/**************************************
staticメンバ
***************************************/
const float BloomController::DefaultPower = 0.8f;
const float BloomController::DefaultThrethold = 0.1f;

/**************************************
コンストラクタ
***************************************/
BloomController::BloomController() :
	bloomPower(),
	bloomThrethold()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//パワーとしきい値の初期化
	bloomPower[0] = bloomPower[1] = bloomPower[2] = DefaultPower;
	bloomThrethold[0] = bloomThrethold[1] = bloomThrethold[2] = DefaultThrethold;

	//縮小バッファの幅と高さを計算
	for (int i = 0; i < NumReduction; i++)
	{
		int reduction = (int)pow(2.0f, i + 2.0f);
		reducedWidth[i] = SCREEN_WIDTH / reduction;
		reducedHeight[i] = SCREEN_HEIGHT / reduction;
	}

	//ブルームブレンダー作成
	bloomBlender = new BloomFilter(SCREEN_WIDTH, SCREEN_HEIGHT);

	//ブルームフィルタ作成
	for (int i = 0; i < 3; i++)
	{
		bloomFilter[i] = new BloomFilter(reducedWidth[i], reducedHeight[i]);
	}

	//ブラーフィルタ作成
	for (int i = 0; i < 3; i++)
	{
		blurFilter[i] = new BlurFilter(reducedWidth[i], reducedHeight[i]);
	}

	//テクスチャ、サーフェイスを設定
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pDevice->CreateTexture(reducedWidth[i], reducedHeight[i], 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &blurTexture[i][j], 0);
			blurTexture[i][j]->GetSurfaceLevel(0, &blurSurface[i][j]);
		}

		//ブラーフィルタ用のビューポートを設定
		blurViewPort[i].Width = reducedWidth[i];
		blurViewPort[i].Height = reducedHeight[i];
		blurViewPort[i].X = 0;
		blurViewPort[i].Y = 0;
		blurViewPort[i].MinZ = 0.0f;
		blurViewPort[i].MaxZ = 1.0f;
	}
}

/**************************************
デストラクタ
***************************************/
BloomController::~BloomController()
{
	for (int i = 0; i < NumReduction; i++)
	{
		for (int j = 0; j < NumBlur; j++)
		{
			SAFE_RELEASE(blurTexture[i][j]);
			SAFE_RELEASE(blurSurface[i][j]);
		}

		SAFE_DELETE(bloomFilter[i]);
		SAFE_DELETE(blurFilter[i]);
	}

	SAFE_DELETE(bloomBlender);
}

/**************************************
描画処理
***************************************/
void BloomController::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ブラー処理をするのでサンプリングをCLAMPに設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//ビューポートを退避
	pDevice->GetViewport(&oldViewPort);

	//現在のレンダーターゲットを退避
	LPDIRECT3DSURFACE9 oldSurface;
	pDevice->GetRenderTarget(0, &oldSurface);

	//輝度抽出処理
	SampleBrightness(texture);

	//抽出した輝度をブラー処理
	ProcessBlur();

	//レンダーターゲットを元に戻す
	pDevice->SetRenderTarget(0, oldSurface);
	SAFE_RELEASE(oldSurface);

	//ブルーム合成
	BlendBloom();

	//サンプリングをもとに戻す
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

#ifdef DEBUG_BLOOM
	Debug::Begin("Bloom");
	for (int i = 0; i < 3; i++)
	{
		Debug::DrawTexture(blurTexture[i][0], { 200.0f, 100.0f });
		Debug::SameLine();
	}
	Debug::End();
#endif
}

/**************************************
パワー設定処理
***************************************/
void BloomController::SetPower(float power1, float power2, float power3)
{
	bloomPower[0] = power1;
	bloomPower[1] = power2;
	bloomPower[2] = power3;
}

/**************************************
しきい値設定処理
***************************************/
void BloomController::SetThrethold(float threthold1, float threthold2, float threthold3)
{
	bloomThrethold[0] = threthold1;
	bloomThrethold[1] = threthold2;
	bloomThrethold[2] = threthold3;
}

/**************************************
明度抽出処理
***************************************/
void BloomController::SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < 3; i++)
	{
		//レンダーターゲットを設定しクリア
		pDevice->SetRenderTarget(0, blurSurface[i][0]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

		//ビューポートを設定
		pDevice->SetViewport(&blurViewPort[i]);

		//ブルームのパラメータを設定
		bloomFilter[i]->SetBloomPower(bloomPower[i]);
		bloomFilter[i]->SetThrethold(bloomThrethold[i]);

		pDevice->SetTexture(0, targetTexture);

		bloomFilter[i]->DrawEffect(0);
	}
}

/**************************************
ブラー処理
***************************************/
void BloomController::ProcessBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int PassMax = 2;

	//ブラー用のサーフェイスをクリア
	for (int i = 0; i < 3; i++)
	{
		pDevice->SetRenderTarget(0, blurSurface[i][1]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);
	}

	for (int cntReduction = 0; cntReduction < 3; cntReduction++)
	{
		//ビューポートを設定
		pDevice->SetViewport(&blurViewPort[cntReduction]);

		cntBlur = 1;

		//ブラー処理
		const int BlurLoop = 4;
		for (int cntBlur = 0; cntBlur < BlurLoop; cntBlur++)
		{
			pDevice->SetRenderTarget(0, blurSurface[cntReduction][(cntBlur + 1) % NumBlur]);
			pDevice->SetTexture(0, blurTexture[cntReduction][cntBlur % NumBlur]);
			blurFilter[cntReduction]->DrawEffect(cntBlur % PassMax);
		}
	}

	//ビューポートをもとに戻す
	pDevice->SetViewport(&oldViewPort);
}

/**************************************
ブルーム合成処理
***************************************/
void BloomController::BlendBloom()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューポートをもとに戻す
	pDevice->SetViewport(&oldViewPort);

	for (int i = 0; i < NumReduction; i++)
	{
		pDevice->SetTexture(i, blurTexture[i][cntBlur % 2]);
	}
	bloomBlender->DrawEffect(1);
}