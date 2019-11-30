//=============================================================================
//
// テクスチャ描画基底クラス [BaseTextureDrawer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "BaseTextureDrawer.h"
#include "../../../../Framework/Resource/ResourceManager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
BaseTextureDrawer::BaseTextureDrawer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
BaseTextureDrawer::~BaseTextureDrawer()
{
	SAFE_RELEASE(Texture);
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void BaseTextureDrawer::LoadTexture(const char *path)
{
	ResourceManager::Instance()->GetTexture(path, Texture);
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void BaseTextureDrawer::LoadTexture(LPDIRECT3DTEXTURE9 *Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = *Texture;
}

//=============================================================================
// オブジェクト描画処理
//=============================================================================
void BaseTextureDrawer::Draw()
{
	// 可視化フラグ、展開処理が必要
	if (!Visible)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, Texture);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//=============================================================================
// テクスチャのアルファ値設定処理（透過）
//=============================================================================
void BaseTextureDrawer::SetAlpha(float alpha)
{
	D3DXCOLOR Color = Vertex[0].diffuse;
	Color.a = alpha;

	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//=============================================================================
// テクスチャの色設定処理
//=============================================================================
void BaseTextureDrawer::SetColor(D3DXCOLOR Color)
{
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}