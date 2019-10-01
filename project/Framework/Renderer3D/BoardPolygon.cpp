//=====================================
//
//板ポリゴン処理[BoardPolygon.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BoardPolygon.h"
#include "../Resource/ResourceManager.h"

/**************************************
マクロ定義
***************************************/
#define BILLBOARD_DEFAULT_SIZE		(10.0f)

/**************************************
AddRef関数
***************************************/
void BoardPolygon::AddRef()
{
	cntReference++;
}

/**************************************
コンストラクタ
***************************************/
BoardPolygon::BoardPolygon()
{
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_MATERIAL) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_MATERIAL,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_DEFAULT_SIZE, BILLBOARD_DEFAULT_SIZE, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( BILLBOARD_DEFAULT_SIZE, BILLBOARD_DEFAULT_SIZE, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-BILLBOARD_DEFAULT_SIZE, -BILLBOARD_DEFAULT_SIZE, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( BILLBOARD_DEFAULT_SIZE, -BILLBOARD_DEFAULT_SIZE, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vtxBuff->Unlock();

	//マテリアル初期化
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Diffuse.g = material.Diffuse.b = material.Diffuse.a = 1.0f;
	material.Ambient.r = material.Ambient.g = material.Ambient.b = material.Ambient.a = 1.0f;
	material.Emissive.r = material.Emissive.g = material.Emissive.b = material.Emissive.a = 1.0f;
	material.Specular.r = material.Specular.g = material.Specular.b = material.Specular.a = 1.0f;
	material.Power = 0.0f;

	cntReference++;
}

/**************************************
デストラクタ
***************************************/
BoardPolygon::~BoardPolygon()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
描画処理
***************************************/
void BoardPolygon::Draw()
{
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	pDevice->SetMaterial(&material);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_MATERIAL));

	pDevice->SetFVF(FVF_VERTEX_MATERIAL);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetMaterial(&matDef);
}

/**************************************
テクスチャ読み込み処理
***************************************/
void BoardPolygon::LoadTexture(const char* path)
{
	SAFE_RELEASE(texture);

	ResourceManager::Instance()->GetTexture(path, texture);
}

/**************************************
サイズ設定処理
***************************************/
void BoardPolygon::SetSize(const D3DXVECTOR2& size)
{
	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( size.x, size.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( size.x, -size.y, 0.0f);

	vtxBuff->Unlock();
}

/**************************************
UV分割設定処理
***************************************/
void BoardPolygon::SetTexDiv(const D3DXVECTOR2& div)
{
	texDiv = div;
	texSize.x = 1.0f / div.x;
	texSize.y = 1.0f / div.y;

	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(texSize.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, texSize.y);
	pVtx[3].tex = D3DXVECTOR2(texSize.x, texSize.y);

	vtxBuff->Unlock();
}

/**************************************
UVインデックス設定処理
***************************************/
void BoardPolygon::SetTextureIndex(int index)
{
	int x = index % (int)texDiv.x;
	int y = index / (int)texDiv.x;

	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(x * texSize.x, y * texSize.y);
	pVtx[1].tex = D3DXVECTOR2((x + 1) * texSize.x, y * texSize.y);
	pVtx[2].tex = D3DXVECTOR2(x * texSize.x, (y + 1) * texSize.y);
	pVtx[3].tex = D3DXVECTOR2((x + 1) * texSize.x, (y + 1) * texSize.y);

	vtxBuff->Unlock();
}