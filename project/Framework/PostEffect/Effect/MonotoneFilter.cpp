//=====================================
//
//モノトーンフィルタ処理[MonotoneFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MonotoneFilter.h"
#include "../../Math/TMath.h"

/**************************************
マクロ定義
***************************************/
#define EFFECTFILE_MONOTONE_PATH	"PostEffect/MonotoneFilter.fx"
#define PRECOMPILE_MONOTONE_PATH	"data/EFFECT/MonotoneFilter.cfx"

/**************************************
グローバル変数
***************************************/
MonotoneFilter* MonotoneFilter::instance = NULL;

/**************************************
インスタンス参照処理
***************************************/
MonotoneFilter* MonotoneFilter::Instance()
{
	if (MonotoneFilter::instance == NULL)
		MonotoneFilter::instance = new MonotoneFilter();

	return MonotoneFilter::instance;
}

/**************************************
インスタンス解放処理
***************************************/
void MonotoneFilter::Destroy()
{
	delete MonotoneFilter::instance;
}

/**************************************
コンストラクタ
***************************************/
MonotoneFilter::MonotoneFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_MONOTONE_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(!res)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_MONOTONE_PATH, 0, 0, 0, 0, &effect, 0);

	effect->SetTechnique("tech");
	hndlPower = effect->GetParameterByName(0, "power");
}

/**************************************
デストラクタ
***************************************/
MonotoneFilter::~MonotoneFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void MonotoneFilter::Draw()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
強さ設定処理
***************************************/
void MonotoneFilter::SetPower(float power)
{
	effect->SetFloat(hndlPower, Math::Clamp(0.0f, 1.0f, power));
	effect->CommitChanges();
}