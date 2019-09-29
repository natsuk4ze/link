//=====================================
//
//ポリゴン2D処理[Polygon2D.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Polygon2D.h"

/**************************************
マクロ定義
***************************************/
#define POLYGON2D_DEFAULT_SIZE		(20.0f)

/**************************************
コンストラクタ
***************************************/
Polygon2D::Polygon2D() :
	texture(NULL)
{
	vtxPos[0] = D3DXVECTOR3(-POLYGON2D_DEFAULT_SIZE, -POLYGON2D_DEFAULT_SIZE, 0.0f);
	vtxPos[1] = D3DXVECTOR3( POLYGON2D_DEFAULT_SIZE, -POLYGON2D_DEFAULT_SIZE, 0.0f);
	vtxPos[2] = D3DXVECTOR3(-POLYGON2D_DEFAULT_SIZE, POLYGON2D_DEFAULT_SIZE, 0.0f);
	vtxPos[3] = D3DXVECTOR3( POLYGON2D_DEFAULT_SIZE, POLYGON2D_DEFAULT_SIZE, 0.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	pDevice = GetDevice();
}

/**************************************
デストラクタ
***************************************/
Polygon2D::~Polygon2D()
{
	SAFE_RELEASE(texture);
}

/**************************************
描画処理
***************************************/
void Polygon2D::Draw()
{
	pDevice->SetTexture(0, texture);

	pDevice->SetFVF(FVF_VERTEX_2D);

	SetVertex();

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
サイズセット処理
***************************************/
void Polygon2D::SetSize(float x, float y)
{
	vtxPos[0] = D3DXVECTOR3(-x, -y, 0.0f);
	vtxPos[1] = D3DXVECTOR3( x, -y, 0.0f);
	vtxPos[2] = D3DXVECTOR3(-x,  y, 0.0f);
	vtxPos[3] = D3DXVECTOR3( x,  y, 0.0f);
}

/**************************************
カラーセット処理
***************************************/
void Polygon2D::SetColor(D3DXCOLOR color)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = color;
}

/**************************************
UV座標設定処理
***************************************/
void Polygon2D::SetUV(float left, float top, float width, float height)
{
	vtxWk[0].tex = D3DXVECTOR2(left, top);
	vtxWk[1].tex = D3DXVECTOR2(left + width, top);
	vtxWk[2].tex = D3DXVECTOR2(left, top + height);
	vtxWk[3].tex = D3DXVECTOR2(left + width, top + height);
}

/**************************************
テクスチャ読み込み処理
***************************************/
void Polygon2D::LoadTexture(const char* path)
{
	SAFE_RELEASE(texture);

	D3DXCreateTextureFromFile(pDevice, path, &texture);
}

/**************************************
頂点座標設定処理
***************************************/
void Polygon2D::SetVertex()
{
	D3DXMATRIX mtxTransform = transform->GetMatrix();

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		D3DXVec3TransformCoord(&vtxWk[i].vtx, &vtxPos[i], &mtxTransform);
	}
}