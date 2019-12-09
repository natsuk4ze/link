//=====================================
//
//MeshField.cpp
//機能:メッシュフィールド
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MeshField.h"
#include "../Resource/ResourceManager.h"

/**************************************
コンストラクタ
***************************************/
MeshField::MeshField(int numBlockX, int numBlockZ, float sizeBlockX, float sizeBlockZ) :
	numBlockX(numBlockX),
	numBlockZ(numBlockZ),
	sizeBlockX(sizeBlockX),
	sizeBlockZ(sizeBlockZ),
	numVertex(0),
	numIndex(0),
	numPolygon(0),
	vtxBuff(NULL),
	indexBuff(NULL),
	texture(NULL)
{
	numVertex = (numBlockX + 1) * (numBlockZ + 1);
	numIndex = (numBlockX + 1) * 2 * numBlockZ + (numBlockZ - 1) * 2;
	numPolygon = numBlockX * numBlockZ * 2 + (numBlockZ - 1) * 4;

	CreateVertexBuffer();

	CreateIndexBuffer();
}

/**************************************
デストラクタ
***************************************/
MeshField::~MeshField()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(texture);
}

/**************************************
描画処理
***************************************/
void MeshField::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(indexBuff);

	pDevice->SetTexture(0, texture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	transform->SetWorld();

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVertex, 0, numPolygon);
}

/**************************************
テクスチャ読み込み
***************************************/
void MeshField::LoadTexture(const char * path)
{
	SAFE_RELEASE(texture);
	ResourceManager::Instance()->GetTexture(path, texture);
}

/**************************************
頂点バッファ作成
***************************************/
void MeshField::CreateVertexBuffer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * numVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	VERTEX_3D *pVtx = NULL;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtxZ = 0; nCntVtxZ < (numBlockZ + 1); nCntVtxZ++)
	{
		for (int nCntVtxX = 0; nCntVtxX < (numBlockX + 1); nCntVtxX++)
		{
			// 頂点座標の設定
			pVtx[nCntVtxZ * (numBlockX + 1) + nCntVtxX].vtx.x = -(numBlockX / 2.0f) * sizeBlockX + nCntVtxX * sizeBlockX;

			pVtx[nCntVtxZ * (numBlockX + 1) + nCntVtxX].vtx.y = 0.0f;

			pVtx[nCntVtxZ * (numBlockX + 1) + nCntVtxX].vtx.z = (numBlockZ / 2.0f) * sizeBlockZ - nCntVtxZ * sizeBlockZ;

			// 反射光の設定
			pVtx[nCntVtxZ * (numBlockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtxZ * (numBlockX + 1) + nCntVtxX].tex.x = (float)nCntVtxX;
			pVtx[nCntVtxZ * (numBlockX + 1) + nCntVtxX].tex.y = (float)nCntVtxZ;
		}
	}

	for (int nZ = 0; nZ < (numBlockZ + 1); nZ++)
	{
		for (int nX = 0; nX < (numBlockX + 1); nX++)
		{
			pVtx[nZ * (numBlockX + 1) + nX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);
		}
	}

	// 頂点データをアンロックする
	vtxBuff->Unlock();
}

/**************************************
インデックスバッファ作成
***************************************/
void MeshField::CreateIndexBuffer()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateIndexBuffer(sizeof(WORD) * numIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&indexBuff,
		NULL);

	WORD *pIdx;

	// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
	indexBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < numBlockZ; nCntVtxZ++)
	{
		if (nCntVtxZ > 0)
		{// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (numBlockX + 1);
			nCntIdx++;
		}

		for (int nCntVtxX = 0; nCntVtxX < (numBlockX + 1); nCntVtxX++)
		{
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (numBlockX + 1) + nCntVtxX;
			nCntIdx++;
			pIdx[nCntIdx] = nCntVtxZ * (numBlockX + 1) + nCntVtxX;
			nCntIdx++;
		}

		if (nCntVtxZ < (numBlockZ - 1))
		{// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = nCntVtxZ * (numBlockX + 1) + numBlockX;
			nCntIdx++;
		}
	}

	// インデックスデータをアンロックする
	indexBuff->Unlock();
}
