//=============================================================================
//
// テロップ描画用処理 [TelopDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include"../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "TelopDrawer.h"

//=============================================================================
// グローバル変数
//=============================================================================

//背景開閉間隔
static const float bgCloseOpenDuration = 15.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
TelopDrawer::TelopDrawer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
TelopDrawer::~TelopDrawer()
{
}

//=============================================================================
// 背景テクスチャの頂点の作成
//=============================================================================
void TelopDrawer::MakeVertexBG()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(3.0, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(3.0f, 1.0f);
}

//=============================================================================
// テキストテクスチャの頂点の作成
//=============================================================================
void TelopDrawer::MakeVertexText()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);

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
// オブジェクトの頂点座標の設定
//=============================================================================
void TelopDrawer::SetVertex()
{
	// 頂点座標の設定
	vertexWk[0].vtx = position + D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = position + D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = position + D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = position + D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
// 背景の頂点座標の設定
//=============================================================================
void TelopDrawer::SetVertexBG(float percentage)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(0, position.y - size.y*percentage, position.z);
	vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y - size.y*percentage, position.z);
	vertexWk[2].vtx = D3DXVECTOR3(0, position.y + size.y*percentage, position.z);
	vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, position.y + size.y*percentage, position.z);
}

//=============================================================================
// 背景を開く処理
//=============================================================================
void TelopDrawer::OpenBG(void)
{
	bgEasingStart = 0.0f;
	bgEasingGoal = 1.0f;

	percentage = Easing::EaseValue(GetCountObject(bgCloseOpenDuration), bgEasingStart, bgEasingGoal, InOutCubic);

	if (percentage >= bgEasingGoal)
	{
		isBG_Openinig = false;
		percentage = 1.0f;
		countFrame = 0;
	}
}

//=============================================================================
// 背景を閉じる処理
//=============================================================================
void TelopDrawer::CloseBG(void)
{
	bgEasingStart = 1.0f;
	bgEasingGoal = 0.0f;

	percentage = Easing::EaseValue(GetCountObject(bgCloseOpenDuration), bgEasingStart, bgEasingGoal, InOutCubic);

	if (percentage <= bgEasingGoal)
	{
		isBG_Closing = false;
		percentage = 0.0f;
		countFrame = 0;
	}
}

//=============================================================================
// オブジェクトカウント取得処理
//=============================================================================
float TelopDrawer::GetCountObject(float duration)
{
	countFrame++;
	float t = (float)countFrame / duration;

	return t;
}

//=============================================================================
// 背景アニメーション再生処理
//=============================================================================
void TelopDrawer::PlayBG(void)
{
	if (isBG_Openinig) 
	{
		OpenBG();
	}

	if (isBG_Closing)
	{
		CloseBG();
	}
}

//=============================================================================
// 背景を開くことを開始
//=============================================================================
void TelopDrawer::PlayBG_Open(void)
{
	isBG_Openinig = true;
}

//=============================================================================
// 背景を閉じることを開始
//=============================================================================
void TelopDrawer::PlayBG_Close(void)
{
	isBG_Closing = true;
}
