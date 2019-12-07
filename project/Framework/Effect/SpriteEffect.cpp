//=====================================
//
//SpriteEffect.cpp
//機能:スプライト描画用エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpriteEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
staticメンバ
***************************************/
D3DXMATRIX SpriteEffect::mtxScreenProj;

/**************************************
コンストラクタ
***************************************/
SpriteEffect::SpriteEffect(const D3DXVECTOR2 & texDiv) :
	diffuse(1.0f, 1.0f, 1.0f, 1.0f),
	texDiv(texDiv),
	texSize(1.0f / texDiv.x, 1.0f / texDiv.y),
	uv(0.0f, 0.0f)
{
	//エフェクト読み込み
	ResourceManager::Instance()->GetEffect("data/EFFECT/Sprite.cfx", effect);

	//ハンドル取得
	hWorld = effect->GetParameterByName(0, "mtxWorld");
	hView = effect->GetParameterByName(0, "mtxView");
	hProjection = effect->GetParameterByName(0, "mtxProj");
	hMtxScreenProj = effect->GetParameterByName(0, "mtxScreenProj");
	hTexUV = effect->GetParameterByName(0, "texUV");
	hDiffuse = effect->GetParameterByName(0, "diffuse");
}

/**************************************
コンストラクタ
***************************************/
SpriteEffect::SpriteEffect(const char*  effectPath, const D3DXVECTOR2& texDiv) :
	diffuse(1.0f, 1.0f, 1.0f, 1.0f),
	texDiv(texDiv),
	texSize(1.0f / texDiv.x, 1.0f / texDiv.y),
	uv(0.0f, 0.0f)
{
	//エフェクト読み込み
	ResourceManager::Instance()->GetEffect(effectPath, effect);

	//ハンドル取得
	hWorld = effect->GetParameterByName(0, "mtxWorld");
	hView = effect->GetParameterByName(0, "mtxView");
	hProjection = effect->GetParameterByName(0, "mtxProj");
	hMtxScreenProj = effect->GetParameterByName(0, "mtxScreenProj");
	hTexUV = effect->GetParameterByName(0, "texUV");
	hDiffuse = effect->GetParameterByName(0, "diffuse");
}

/**************************************
デストラクタ
***************************************/
SpriteEffect::~SpriteEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
変更反映処理
***************************************/
void SpriteEffect::Commit()
{	
	effect->SetMatrix(hView, &mtxView);
	effect->SetMatrix(hProjection, &mtxProjection);
	effect->SetMatrix(hMtxScreenProj, &mtxScreenProj);
	effect->SetFloatArray(hDiffuse, (float*)&diffuse, 4);
	effect->SetFloatArray(hTexUV, (float*)&uv, 2);
	effect->CommitChanges();
}

/**************************************
ワールド変換行列セット処理
***************************************/
void SpriteEffect::SetWorld(const D3DXMATRIX & mtxWorld)
{
	effect->SetMatrix(hWorld, &mtxWorld);
}

/**************************************
ディフューズ設定処理
***************************************/
void SpriteEffect::SetDiffuse(const D3DXCOLOR & color)
{
	diffuse = color;
}

/**************************************
テクスチャ分割数設定処理
***************************************/
void SpriteEffect::SetTextureDivine(const D3DXVECTOR2 & divine)
{
	texDiv = divine;
	texSize.x = 1.0f / texDiv.x;
	texSize.y = 1.0f / texDiv.y;
}

/**************************************
テクスチャ通し番号設定処理
***************************************/
void SpriteEffect::SetTextureIndex(int index)
{
	int u = index % (int)texDiv.x;
	int v = index / (int)texDiv.x;

	uv.x = u * texSize.x;
	uv.y = v * texSize.y;
}

/**************************************
スクリーン投影行列設定処理
***************************************/
void SpriteEffect::SetScreenProjection(const D3DXMATRIX & mtx)
{
	mtxScreenProj = mtx;
}
