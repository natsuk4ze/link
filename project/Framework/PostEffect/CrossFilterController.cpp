//=====================================
//
//クロスフィルタコントローラ処理[CrossFilterController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CrossFilterController.h"

/**************************************
マクロ定義
***************************************/
#define CROSSFILTER_THRETHOLD_DEFAULT	(0.2f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
更新処理
***************************************/
void CrossFilterController::Update()
{

}

/**************************************
描画処理
***************************************/
void CrossFilterController::Draw(LPDIRECT3DTEXTURE9 targetTexture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ブラー処理をするのでサンプリングをCLAMPに設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//Zバッファへの書き込みを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//ビューポートを退避
	pDevice->GetViewport(&oldViewPort);

	//レンダーターゲットを退避
	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);

	//輝度抽出処理
	SampleBrightness(targetTexture);

	//抽出した輝度をブラー処理(
	ProcessBlur();

	//レンダーターゲットを元に戻す
	pDevice->SetRenderTarget(0, oldSuf);

	//クロスフィルタ合成
	Blend();

	//レンダーターゲットの参照を解放
	SAFE_RELEASE(oldSuf);

	//Zバッファに書き込むように戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//サンプリングを元に戻す
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

/**************************************
コンストラクタ
***************************************/
CrossFilterController::CrossFilterController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ブルームフィルタのインスタンス、テクスチャ、サーフェイスを設定
	bloomFilter = new BloomFilter();
	bloomFilter->SetThrethold(CROSSFILTER_THRETHOLD_DEFAULT);

	//ブラーフィルタのインスタンスを生成
	blurFilter = new CrossBlurFilter();

	//クロスフィルタ用のテクスチャを作成（１）
	for (int i = 0; i < 3; i++)
	{
		int reduction = (int)powf(2.0f, i + 2.0f);
		for (int j = 0; j < 2; j++)
		{
			pDevice->CreateTexture(SCREEN_WIDTH / reduction,
				SCREEN_HEIGHT / reduction,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_X8R8G8B8,
				D3DPOOL_DEFAULT,
				&blurTexture[i][j],
				0);
			blurTexture[i][j]->GetSurfaceLevel(0, &blurSurface[i][j]);
		}
	}

	//サンプリング用のテクスチャ作成
	pDevice->CreateTexture(SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&sampleTexture,
		0);
	sampleTexture->GetSurfaceLevel(0, &sampleSurface);

	//縮小バッファ用のビューポートを作成
	for (int i = 0; i < 3; i++)
	{
		int reduction = (int)powf(2.0f, i + 2.0f);
		blurViewPort[i].Width = SCREEN_WIDTH / reduction;
		blurViewPort[i].Height = SCREEN_HEIGHT / reduction;
		blurViewPort[i].MinZ = 0.0f;
		blurViewPort[i].MaxZ = 1.0f;
		blurViewPort[i].X = 0;
		blurViewPort[i].Y = 0;
	}
}

/**************************************
デストラクタ
***************************************/
CrossFilterController::~CrossFilterController()
{
	delete blurFilter;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			SAFE_RELEASE(blurTexture[i][j]);
			SAFE_RELEASE(blurSurface[i][j]);
		}

	}
	SAFE_RELEASE(sampleTexture);
	SAFE_RELEASE(sampleSurface);

	delete bloomFilter;
}

/**************************************
輝度抽出処理
***************************************/
void CrossFilterController::SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture)
{
	const float BloomPower[3] = { 0.5f, 0.5f, 0.5f };

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//ビューポートを設定
	pDevice->SetViewport(&blurViewPort[0]);

	//ゲインを設定
	bloomFilter->SetBloomPower(BloomPower[0]);

	//テクスチャ設定
	if (targetTexture != NULL)
		pDevice->SetTexture(0, targetTexture);
	else
		pDevice->SetTexture(0, defaultTarget);

	//縮小バッファ用に頂点をリサイズ
	bloomFilter->Resize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//レンダーターゲットを設定 
	pDevice->SetRenderTarget(0, sampleSurface);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

	//現在の描画情報から輝度を抽出（１）
	bloomFilter->DrawEffect(0);

}

/**************************************
ブラー処理
***************************************/
void CrossFilterController::ProcessBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int Pass = 4;
	const int TextureMax = 2;

	for (int i = 0; i < 3; i++)
	{
		//ビューポートを設定
		pDevice->SetViewport(&blurViewPort[i]);

		float reduction = powf(2.0f, i + 2.0f);
		blurFilter->SetSurfaceSize(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction);

		//サーフェイス0番にサンプル結果を転写
		pDevice->SetRenderTarget(0, blurSurface[i][0]);
		pDevice->SetTexture(0, sampleTexture);
		blurFilter->DrawEffect(Pass);

		cntBlur = 1;

		//ブラー処理
		const int BlurLoop = 2;
		for (int j = 0; j < BlurLoop; j++, cntBlur++)
		{
			pDevice->SetRenderTarget(0, blurSurface[i][cntBlur % TextureMax]);
			pDevice->SetTexture(0, blurTexture[i][(cntBlur + 1) % TextureMax]);
			blurFilter->DrawEffect(Pass);
		}
	}

	//ビューポートを設定に戻す
	pDevice->SetViewport(&oldViewPort);
}

/**************************************
合成処理
***************************************/
void CrossFilterController::Blend()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューポートを元に戻す
	pDevice->SetViewport(&oldViewPort);

	//レンダーステートを加算合成に設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ブラーをかけた結果を加算合成（１）
	bloomFilter->Resize((float)oldViewPort.Width, (float)oldViewPort.Height);

	pDevice->SetTexture(0, blurTexture[0][cntBlur % 2]);
	pDevice->SetTexture(1, blurTexture[1][cntBlur % 2]);
	pDevice->SetTexture(2, blurTexture[2][cntBlur % 2]);

	bloomFilter->DrawEffect(1);

	//レンダーステートを元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}