//=====================================
//
//板ポリゴン処理[BoardPolygon.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BoardPolygon.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/PolygonResource.h"
#include "../Effect/SpriteEffect.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BoardPolygon::BoardPolygon() :
	vtxBuff(nullptr),
	texture(nullptr),
	effect(nullptr)
{
	pDevice = GetDevice();
	effect = new SpriteEffect();
}

/**************************************
コンストラクタ
***************************************/
BoardPolygon::BoardPolygon(SpriteEffect * effect) :
	vtxBuff(nullptr),
	texture(nullptr),
	effect(effect)
{
	pDevice = GetDevice();
}

/**************************************
デストラクタ
***************************************/
BoardPolygon::~BoardPolygon()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
	SAFE_DELETE(effect);

	if (resource != NULL)
		resource->OnRelease();
}

/**************************************
描画処理
***************************************/
void BoardPolygon::Draw(const D3DXMATRIX& mtxWorld)
{
	effect->SetWorld(mtxWorld);
	effect->Commit();

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_MATERIAL));

	pDevice->SetFVF(FVF_VERTEX_MATERIAL);

	effect->Begin();
	effect->BeginPass(0);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	effect->EndPass();
	effect->End();
}

/**************************************
UV分割設定処理
***************************************/
void BoardPolygon::SetTexDiv(const D3DXVECTOR2& div)
{
	effect->SetTextureDivine(div);
}

/**************************************
UVインデックス設定処理
***************************************/
void BoardPolygon::SetTextureIndex(int index)
{
	effect->SetTextureIndex(index);
}

/**************************************
ディフューズ設定処理
***************************************/
void BoardPolygon::SetDiffuse(const D3DXCOLOR & color)
{
	effect->SetDiffuse(color);
}
