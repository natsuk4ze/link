//=====================================
//
//スピードブラーフィルター処理[SpeedBlurFilter.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "SpeedBlurFilter.h"

/**************************************
マクロ定義
***************************************/
#define EFEFCTFILE_SPEEDBLUR_PATH		"PostEffect/SpeedBlur.fx"
#define PRECOMPILE_SPEEDBLUR_PATH		"data/EFFECT/SpeedBlur.cfx"

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
SpeedBlur::SpeedBlur(DWORD width, DWORD height) :
	ScreenObject(height, width)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_SPEEDBLUR_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if (res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFEFCTFILE_SPEEDBLUR_PATH, 0, 0, 0, 0, &effect, 0);

	hPower = effect->GetParameterByName(0, "blurPower");
	hCenter = effect->GetParameterByName(0, "centerTexel");
	hTU = effect->GetParameterByName(0, "tU");
	hTV = effect->GetParameterByName(0, "tV");
	hStartLength = effect->GetParameterByName(0, "startLength");
	hAspectRatio = effect->GetParameterByName(0, "aspectRatio");

	SetAspectRatio((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
}

/**************************************
デストラクタ
***************************************/
SpeedBlur::~SpeedBlur()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void SpeedBlur::DrawEffect()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
パワーセット処理
***************************************/
void SpeedBlur::SetPower(float power)
{
	effect->SetFloat(hPower, power);
	effect->CommitChanges();
}

/**************************************
センターセット処理
***************************************/
void SpeedBlur::SetCenterPos(D3DXVECTOR3 pos)
{
	D3DXMATRIX view, proj;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVIEWPORT9 viewport;
	D3DXVECTOR3 center;

	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetViewport(&viewport);

	D3DXVec3TransformCoord(&center, &pos, &view);
	D3DXVec3TransformCoord(&center, &center, &proj);
	center.x = (center.x + 1.0f) / 2.0f;
	center.y = (-center.y + 1.0f) / 2.0f;

	effect->SetFloatArray(hCenter, (float*)&center, 2);
	effect->CommitChanges();
}

/**************************************
テクセルサイズ設定処理
***************************************/
void SpeedBlur::SetSurfaceSize(float width, float height)
{
	float texelU = 1.0f / width;
	float texelV = 1.0f / height;

	effect->SetFloat(hTU, texelU);
	effect->SetFloat(hTV, texelV);
	effect->CommitChanges();
}

/**************************************
ブラー開始距離セット処理
***************************************/
void SpeedBlur::SetStartLength(float length)
{
	effect->SetFloat(hStartLength, length);
	effect->CommitChanges();
}

/**************************************
アスペクト比設定処理
***************************************/
void SpeedBlur::SetAspectRatio(float width, float height)
{
	effect->SetFloat(hAspectRatio, height / width);
	effect->CommitChanges();
}