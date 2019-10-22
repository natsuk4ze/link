//=====================================
//
//ブルームコントローラ処理[BloomController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BloomController.h"
#include "../Tool/DebugWindow.h"

#define DEBGU_BLOOM
/**************************************
staticメンバ
***************************************/
const float BloomController::DefaultPower = 0.3f;
const float BloomController::DefaultThrethold = 0.4f;

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

	//ブルームフィルタのインスタンス、テクスチャ、サーフェイスを設定
	bloomFilter = new BloomFilter(SCREEN_WIDTH, SCREEN_HEIGHT);

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

#ifdef _DEBUG_BLOOM
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
		bloomFilter->SetBloomPower(bloomPower[i]);
		bloomFilter->SetThrethold(bloomThrethold[i]);

		float reduction = powf(2.0f, i + 2.0f);
		bloomFilter->Resize(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction);

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
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	bloomFilter->Resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	pDevice->SetTexture(0, blurTexture[0][cntBlur % 2]);
	pDevice->SetTexture(1, blurTexture[1][cntBlur % 2]);
	pDevice->SetTexture(2, blurTexture[2][cntBlur % 2]);

	bloomFilter->DrawEffect(1);

	//レンダーステートを元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}