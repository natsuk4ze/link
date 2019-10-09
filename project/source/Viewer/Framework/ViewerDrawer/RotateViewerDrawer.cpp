//=============================================================================
//
// 回転ビュアー描画用処理 [UIdrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include "RotateViewerDrawer.h"

//=============================================================================
// オブジェクトサークルの作成　（回転オブジェクト用のサークルを作る）
//=============================================================================
void RotateViewerDrawer::CreateCircle()
{
	D3DXVECTOR2 temp = D3DXVECTOR2(size.x, size.y);
	radius = D3DXVec2Length(&temp);
	baseAngle = atan2f(size.y, size.x);
}

//=============================================================================
// テクスチャの頂点の作成 (回転オブジェクト用)
//=============================================================================
void RotateViewerDrawer::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;

	// テクスチャのパースペクティブコレクト用
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// オブジェクトの頂点座標の設定 (回転オブジェクト用)
//=============================================================================
void RotateViewerDrawer::SetVertex()
{
	// 頂点座標の設定
	vertexWk[0].vtx.x = position.x - cosf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(baseAngle + rotation.z) * radius;
	vertexWk[0].vtx.z = 0.0f;

	vertexWk[1].vtx.x = position.x + cosf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(baseAngle - rotation.z) * radius;
	vertexWk[1].vtx.z = 0.0f;

	vertexWk[2].vtx.x = position.x - cosf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(baseAngle - rotation.z) * radius;
	vertexWk[2].vtx.z = 0.0f;

	vertexWk[3].vtx.x = position.x + cosf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(baseAngle + rotation.z) * radius;
	vertexWk[3].vtx.z = 0.0f;
}
