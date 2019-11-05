//=============================================================================
//
// 基底ビュアー描画用処理 [BaseViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include "BaseViewerDrawer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
BaseViewerDrawer::BaseViewerDrawer()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
BaseViewerDrawer::~BaseViewerDrawer()
{
	SAFE_RELEASE(texture);
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void BaseViewerDrawer::LoadTexture(const char *path)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		path,							// ファイルのアドレス
		&texture);						// 読み込むメモリー
}

//=============================================================================
// オブジェクト描画処理
//=============================================================================
void BaseViewerDrawer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点座標をセット
	SetVertexPos();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
void BaseViewerDrawer::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexPos();

	// テクスチャのパースペクティブコレクト用
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetColor(SET_COLOR_NOT_COLORED);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void BaseViewerDrawer::SetVertexPos()
{
	// 頂点座標の設定
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x/2, -size.y/2, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x/2, -size.y/2, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x/2, size.y/2, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x/2, size.y/2, 0.0f);
}

//=============================================================================
// テクスチャ座標設定処理
//=============================================================================
void BaseViewerDrawer::SetTexture(int divX, int divY, int pattern)
{
	float sizeX = 1.0f / divX;
	float sizeY = 1.0f / divY;
	int x = pattern % divX;
	int y = pattern / divX;

	vertexWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vertexWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vertexWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1)* sizeY);
	vertexWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

//=============================================================================
//オブジェクトのアルファ値設定処理　（透過）
//=============================================================================
void BaseViewerDrawer::SetAlpha(float alpha)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

//=============================================================================
//オブジェクトの反射光設定処理
//=============================================================================
void BaseViewerDrawer::SetColor(D3DXCOLOR color)
{
	vertexWk[0].diffuse =
		vertexWk[1].diffuse =
		vertexWk[2].diffuse =
		vertexWk[3].diffuse = color;
}
