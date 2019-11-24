//=====================================
//
// サブスクリーン[SubScreen.cpp]
// 機能：描画用サブスクリーン作成クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "SubScreen.h"

//=====================================
// コンストラクタ
//=====================================
SubScreen::SubScreen(D3DXVECTOR2 size, D3DXVECTOR2 position)
{
	this->size = size;
	this->position = position;

	MakeScreen();
	MakeRenderTarget();
}

//=====================================
// デストラクタ
//=====================================
SubScreen::~SubScreen()
{
	SAFE_RELEASE(renderTexture);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(oldSuface);
	SAFE_RELEASE(screenVtx);
}

//=====================================
// 描画はじめ
//=====================================
void SubScreen::DrawBegin(const D3DXCOLOR& backColor)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット切り替え
	pDevice->GetRenderTarget(0, &oldSuface);
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

//=====================================
// 描画
//=====================================
void SubScreen::DrawTexture()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetTexture(0, renderTexture);
}

//=====================================
// 描画終わり
//=====================================
void SubScreen::DrawEnd()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット復元
	pDevice->SetRenderTarget(0, oldSuface);

	//バックバッファへ描画
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetStreamSource(0, screenVtx, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// レンダーターゲットの作成
//=====================================
void SubScreen::MakeRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーテクスチャ作成
	pDevice->CreateTexture((UINT)size.x,
		(UINT)size.y,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	renderTexture->GetSurfaceLevel(0, &renderSurface);
}

//=====================================
// スクリーンの作成
//=====================================
void SubScreen::MakeScreen()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&screenVtx,
		0);

	VERTEX_2D *pVtx;
	screenVtx->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(position.x, position.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position.x + size.x, position.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position.x, position.y + size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position.x + size.x, position.y + size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	screenVtx->Unlock();
}
