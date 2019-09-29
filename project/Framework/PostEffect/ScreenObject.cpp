//=====================================
//
//スクリーンオブジェクト処理[ScreenObject.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ScreenObject.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
ScreenObject::ScreenObject()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&this->vtxBuff,
		0);

	//頂点バッファに初期値を設定
	VERTEX_2D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	vtxBuff->Unlock();

	Resize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************
デストラクタ
***************************************/
ScreenObject::~ScreenObject()
{
	SAFE_RELEASE(vtxBuff);
}

/**************************************
描画処理
***************************************/
void ScreenObject::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
サイズ変更処理
***************************************/
void ScreenObject::Resize(float width, float height)
{
	VERTEX_2D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の変換
	pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(width, 0.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f, height, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(width, height, 0.0f);

	//射影空間からUV座標空間への変換
	float offsetU = 0.5f / width;
	float offsetV = 0.5f / height;
	pVtx[0].tex = D3DXVECTOR2(0.0f + offsetU, 0.0f + offsetV);
	pVtx[1].tex = D3DXVECTOR2(1.0f + offsetU, 0.0f + offsetV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + offsetU, 1.0f + offsetV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + offsetU, 1.0f + offsetV);

	vtxBuff->Unlock();

}