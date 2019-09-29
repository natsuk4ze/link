//=====================================
//
//クロスブラーフィルター処理[CrossBlurFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CrossBlurFilter.h"

/**************************************
マクロ定義
***************************************/
#define EFFECTFILE_CROSSBLUR_PATH	"PostEffect/CrossBlur.fx"
#define PRECOMPILE_CROSSBLUR_PATH	"data/EFFECT/CrossBlur.cfx"
#define CROSSBLUR_ARRAY_SIZE		(2)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
CrossBlurFilter::CrossBlurFilter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_CROSSBLUR_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_CROSSBLUR_PATH, 0, 0, 0, 0, &effect, 0);

	hTexelU = effect->GetParameterByName(0, "texelU");
	hTexelV = effect->GetParameterByName(0, "texelV");
	effect->SetTechnique("tech");
}

/**************************************
デストラクタ
***************************************/
CrossBlurFilter::~CrossBlurFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void CrossBlurFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
サーフェイスサイズ設定処理
***************************************/
void CrossBlurFilter::SetSurfaceSize(float width, float height)
{
	float u[CROSSBLUR_ARRAY_SIZE], v[CROSSBLUR_ARRAY_SIZE];
	
	for(int i = 0; i < CROSSBLUR_ARRAY_SIZE; i++)
	{
		u[i] = 1.0f / width * (i + 1);
		v[i] = 1.0f / height * (i + 1);
	}

	effect->SetFloatArray(hTexelU, u, CROSSBLUR_ARRAY_SIZE);
	effect->SetFloatArray(hTexelV, v, CROSSBLUR_ARRAY_SIZE);
	effect->CommitChanges();

	ScreenObject::Resize(width, height);
}