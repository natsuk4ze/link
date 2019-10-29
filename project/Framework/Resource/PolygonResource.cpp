//=====================================
//
//PolygonResource.cpp
//機能:ポリゴンリソース
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PolygonResource.h"
#include "../Renderer3D/BoardPolygon.h"

/**************************************
コンストラクタ
***************************************/
PolygonResource::PolygonResource(const D3DXVECTOR2 & size, const D3DXVECTOR2 & uv, const char* path) :
	vtxBuff(nullptr),
	texture(nullptr),
	cntRef(0)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_MATERIAL) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_MATERIAL,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	//頂点バッファ初期化
	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(size.x, size.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(size.x, -size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / uv.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / uv.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / uv.x, 1.0f / uv.y);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vtxBuff->Unlock();

	//テクスチャ読み込み
	if (path != nullptr)
	{
		D3DXCreateTextureFromFile(pDevice, path, &texture);
	}
}

/**************************************
デストラクタ
***************************************/
PolygonResource::~PolygonResource()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);

	//クローンしたBoardPolygonが正常に開放されているか確認
	assert(cntRef == 0);
}

/**************************************
クローン
***************************************/
void PolygonResource::Clone(BoardPolygon * entity)
{
	if (entity == nullptr)
		return;

	entity->vtxBuff = vtxBuff;
	vtxBuff->AddRef();

	entity->texture = texture;
	texture->AddRef();

	entity->resource = this;
	cntRef++;
}

/**************************************
リリース時の処理
***************************************/
void PolygonResource::OnRelease()
{
	cntRef--;
}
