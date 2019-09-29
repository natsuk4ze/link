//=====================================
//
//ブルームコントローラ処理[BloomController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloomController.h"

/**************************************
マクロ定義
***************************************/
//#define BLOOM_USE_DEBUG

#ifdef BLOOM_USE_DEBUG
#include "../debugWindow.h"
#endif

#define BLOOM_THRETHOLD_DEFAULT (0.45f)

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
更新処理
***************************************/
void BloomController::Update()
{

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

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

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

	//Zバッファに書き込むように戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//サンプリングをもとに戻す
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

/**************************************
コンストラクタ
***************************************/
BloomController::BloomController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ブルームフィルタのインスタンス、テクスチャ、サーフェイスを設定
	bloomFilter = new BloomFilter();
	bloomFilter->SetThrethold(BLOOM_THRETHOLD_DEFAULT);

	//ブラーフィルタのインスタンス、テクスチャ、サーフェイスを設定
	blurFilter = new BlurFilter();
	for (int i = 0; i < 3; i++)
	{
		int reduction = (int)powf(2.0f, i + 2.0f);
		for (int j = 0; j < 2; j++)
		{
			pDevice->CreateTexture(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &blurTexture[i][j], 0);
			blurTexture[i][j]->GetSurfaceLevel(0, &blurSurface[i][j]);
		}

		//ブラーフィルタ用のビューポートを設定
		blurViewPort[i].Width = SCREEN_WIDTH / reduction;
		blurViewPort[i].Height = SCREEN_HEIGHT / reduction;
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
	delete blurFilter;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SAFE_RELEASE(blurTexture[j][i]);
			SAFE_RELEASE(blurSurface[j][i]);
		}
	}

	delete bloomFilter;
}

/**************************************
明度抽出処理
***************************************/
void BloomController::SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture)
{
	static float BloomPower[3] = { 0.56f, 0.6f, 0.86f };

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < 3; i++)
	{
		//レンダーターゲットを設定しクリア
		pDevice->SetRenderTarget(0, blurSurface[i][0]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

		//ビューポートを設定
		pDevice->SetViewport(&blurViewPort[i]);

		//ブルームのゲインを設定
		bloomFilter->SetBloomPower(BloomPower[i]);

		float reduction = powf(2.0f, i + 2.0f);
		bloomFilter->Resize(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction);

		//現在の描画情報から輝度を抽出
		if (targetTexture == NULL)
			pDevice->SetTexture(0, defaultTarget);
		else
			pDevice->SetTexture(0, targetTexture);

		bloomFilter->DrawEffect(0);
	}
}

/**************************************
ブラー処理
***************************************/
void BloomController::ProcessBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int PassMax = 2;
	const int TextureMax = 2;

	//ブラー用のサーフェイスをクリア
	for (int i = 0; i < 3; i++)
	{
		pDevice->SetRenderTarget(0, blurSurface[i][1]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);
	}

	for (int j = 0; j < 3; j++)
	{
		//ビューポートを設定
		pDevice->SetViewport(&blurViewPort[j]);

		float reduction = powf(2.0f, j + 2.0f);
		blurFilter->SetSurfaceSize(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction);

		cntBlur = 1;

		//ブラー処理
		const int BlurLoop = 3;
		for (int i = 0; i < BlurLoop; i++, cntBlur++)
		{
			pDevice->SetRenderTarget(0, blurSurface[j][cntBlur % TextureMax]);
			pDevice->SetTexture(0, blurTexture[j][(cntBlur + 1) % TextureMax]);
			blurFilter->DrawEffect(cntBlur % PassMax);
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

	//レンダーステートを加算合成に設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	bloomFilter->Resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	pDevice->SetTexture(0, blurTexture[0][cntBlur % 2]);
	pDevice->SetTexture(1, blurTexture[1][cntBlur % 2]);
	pDevice->SetTexture(2, blurTexture[2][cntBlur % 2]);

	bloomFilter->DrawEffect(1);

	//レンダーステートを元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}