//=====================================
//
//クロスフィルタコントローラ処理[CrossFilterController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CrossFilterController.h"
#include "Effect/BloomFilter.h"
#include "Effect/CrossBlurFilter.h"
#include "../Tool/DebugWindow.h"

//#define DEBUG_CROSSFILTER
/**************************************
staticメンバ
***************************************/
const float CrossFilterController::DefaultPower = 1.0f;
const float CrossFilterController::DefaultThrethold = 0.0f;

/**************************************
コンストラクタ
***************************************/
CrossFilterController::CrossFilterController() :
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

	//ブルームフィルタ作成
	for (int i = 0; i < 3; i++)
	{
		bloomFilter[i] = new BloomFilter(reducedWidth[i], reducedHeight[i]);
	}

	//ブラーフィルタ作成
	for (int i = 0; i < 3; i++)
	{
		blurFilter[i] = new CrossBlurFilter(reducedWidth[i], reducedHeight[i]);
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
CrossFilterController::~CrossFilterController()
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
	BlendBloom();

	//レンダーターゲットの参照を解放
	SAFE_RELEASE(oldSuf);

	//Zバッファに書き込むように戻す
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//サンプリングを元に戻す
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

#ifdef DEBUG_CROSSFILTER
	Debug::Begin("CrossFilter");
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
void CrossFilterController::SetPower(float power1, float power2, float power3)
{
	bloomPower[0] = power1;
	bloomPower[1] = power2;
	bloomPower[2] = power3;
}

/**************************************
しきい値設定処理
***************************************/
void CrossFilterController::SetThrethold(float threthold1, float threthold2, float threthold3)
{
	bloomThrethold[0] = threthold1;
	bloomThrethold[1] = threthold2;
	bloomThrethold[2] = threthold3;
}

/**************************************
輝度抽出処理
***************************************/
void CrossFilterController::SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture)
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
void CrossFilterController::ProcessBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int PassMax = 4;
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

		//ブラー処理
		const int BlurLoop = 8;
		for (cntBlur = 0; cntBlur < BlurLoop; cntBlur++)
		{
			pDevice->SetRenderTarget(0, blurSurface[j][(cntBlur + 1) % TextureMax]);
			pDevice->SetTexture(0, blurTexture[j][cntBlur % TextureMax]);
			blurFilter[j]->DrawEffect(cntBlur % PassMax);
		}
	}

	//ビューポートをもとに戻す
	pDevice->SetViewport(&oldViewPort);
}

/**************************************
合成処理
***************************************/
void CrossFilterController::BlendBloom()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューポートをもとに戻す
	pDevice->SetViewport(&oldViewPort);

	//レンダーステートを加算合成に設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (int i = 0; i < NumReduction; i++)
	{
		pDevice->SetTexture(0, blurTexture[0][cntBlur % 2]);
		renderer->Draw();
	}

	//レンダーステートを元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}