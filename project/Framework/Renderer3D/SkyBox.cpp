//=====================================
//
//SkyBox.cpp
//機能:スカイボックス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SkyBox.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
SkyBox::SkyBox(const D3DXVECTOR3 & size)
{
	//テクスチャコンテナ準備
	textureContainer.resize(Surface::Max, NULL);

	//頂点バッファ作成
	MakeVertexBuffer(size.x, size.y, size.z);
}

/**************************************
デストラクタ
***************************************/
SkyBox::~SkyBox()
{
	//テクスチャ解放
	for (auto&& texture : textureContainer)
	{
		SAFE_RELEASE(texture);
	}
	textureContainer.clear();

	//頂点バッファ解放
	SAFE_RELEASE(vtxBuff);
}

/**************************************
描画処理
***************************************/
void SkyBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	D3DXMATRIX mtxWorld;
	transform->SetWorld();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	for (int i = 0; i < Surface::Max; i++)
	{
		pDevice->SetTexture(0, textureContainer[i]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

/**************************************
テクスチャ読み込み処理
***************************************/
void SkyBox::LoadTexture(const char * fileName, Surface surface)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, fileName, &textureContainer[surface]);
}

/**************************************
頂点バッファ作成処理
***************************************/
void SkyBox::MakeVertexBuffer(const float width, const float height, const float depth)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX * Surface::Max,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_BILLBOARD,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_BILLBOARD *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上面
	pVtx[0].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//後面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(-width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//下面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-width, -height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, -height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//前面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//左面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(-width, height, -depth);
	pVtx[1].vtx = D3DXVECTOR3(-width, height, depth);
	pVtx[2].vtx = D3DXVECTOR3(-width, -height, -depth);
	pVtx[3].vtx = D3DXVECTOR3(-width, -height, depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//右面
	pVtx += 4;
	pVtx[0].vtx = D3DXVECTOR3(width, height, depth);
	pVtx[1].vtx = D3DXVECTOR3(width, height, -depth);
	pVtx[2].vtx = D3DXVECTOR3(width, -height, depth);
	pVtx[3].vtx = D3DXVECTOR3(width, -height, -depth);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}
