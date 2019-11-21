//=====================================
//
// ガイドビュアー[GuideViewer.cpp]
// 機能：ガイド役キャラクター表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideViewer.h"
#include "../../../../Framework/Resource/ResourceManager.h"
#include "../../../../Framework/Effect/RendererEffect.h"

//**************************************
// スタティックメンバ初期化
//**************************************
const D3DXVECTOR2 GuideViewer::SubScreenSize = D3DXVECTOR2(360.0f, 360.0f);
const D3DXVECTOR3 GuideViewer::SubScreenPosition = D3DXVECTOR3(30.0f, 690.0f, 0.0f);

//=====================================
// コンストラクタ
//=====================================
GuideViewer::GuideViewer()
{
	// 描画用サブスクリーンの作成
	MakeScreen();
	MakeRenderTarget();

	// リソース読み込み
	ResourceManager::Instance()->MakePolygon("GuideViewerBG", "data/TEXTURE/VIewer/GameViewer/GuideViewer/Circuit.png", D3DXVECTOR2(500.0f, 500.0f));

	// 各種インスタンスの作成
	actor = new GuideActor();
	camera = new GuideCamera();
	bg = new GuideViewerBG();
	filter = new CRTFilter((DWORD)SubScreenSize.x, (DWORD)SubScreenSize.y);

}

//=====================================
// デストラクタ
//=====================================
GuideViewer::~GuideViewer()
{
	SAFE_RELEASE(renderTexture);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(screenVtx);

	SAFE_DELETE(actor);
	SAFE_DELETE(camera);
	SAFE_DELETE(bg);
	SAFE_DELETE(filter);
}

//=====================================
// 更新
//=====================================
void GuideViewer::Update()
{
	camera->Update();
	actor->Update();
	bg->Update();
	filter->SetTime();
	filter->SetScreenParam(SubScreenSize.x, SubScreenSize.y);
}

//=====================================
// 描画
//=====================================
void GuideViewer::Draw()
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット切り替え
	LPDIRECT3DSURFACE9 oldSuf;
	const D3DXCOLOR BackColor = D3DXCOLOR(0.6f, 0.6f, 1.0f, 0.8f);
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BackColor, 1.0f, 0);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	// インスタンスの描画
	bg->Draw();
	actor->Draw();

	for (int i = 0; i < 4; i++)
	{
		pDevice->SetTexture(0, renderTexture);
		filter->Draw(i);
	}

	//レンダーターゲット復元
	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	//バックバッファへ描画
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetStreamSource(0, screenVtx, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// アクターのアニメーション切り替え
//=====================================
void GuideViewer::ChangeAnim(GuideActor::AnimState next)
{
	actor->ChangeAnim(next);
}

//=====================================
// 描画可否判定のセット
//=====================================
void GuideViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=====================================
// レンダーターゲットの作成
//=====================================
void GuideViewer::MakeRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーテクスチャ作成
	pDevice->CreateTexture((UINT)SubScreenSize.x,
		(UINT)SubScreenSize.y,
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
void GuideViewer::MakeScreen()
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

	pVtx[0].vtx = D3DXVECTOR3(SubScreenPosition.x, SubScreenPosition.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(SubScreenPosition.x + SubScreenSize.x, SubScreenPosition.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(SubScreenPosition.x, SubScreenPosition.y + SubScreenSize.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(SubScreenPosition.x + SubScreenSize.x, SubScreenPosition.y + SubScreenSize.y, 0.0f);

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