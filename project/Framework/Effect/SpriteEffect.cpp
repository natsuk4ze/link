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
D3DXMATRIX SpriteEffect::mtxView;
D3DXMATRIX SpriteEffect::mtxProjection;
D3DXMATRIX SpriteEffect::mtxScreenProj;

/**************************************
コンストラクタ
***************************************/
SpriteEffect::SpriteEffect(const D3DXVECTOR2 & texDiv) :
	effect(nullptr),
	diffuse(1.0f, 1.0f, 1.0f, 1.0f),
	texDiv(texDiv),
	texSize(1.0f / texDiv.x, 1.0f / texDiv.y),
	uv(0.0f, 0.0f)
{
	//エフェクト読み込み
	ResourceManager::Instance()->GetEffect("data/EFFECT/Sprite.cfx", effect);

	//ハンドル取得
	hMtxWorld = effect->GetParameterByName(0, "mtxWorld");
	hMtxView = effect->GetParameterByName(0, "mtxView");
	hMtxProj = effect->GetParameterByName(0, "mtxProj");
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
開始処理
***************************************/
void SpriteEffect::Begin()
{
	effect->Begin(0, 0);
}

/**************************************
パス開始ショリ
***************************************/
void SpriteEffect::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
パス終了処理
***************************************/
void SpriteEffect::EndPass()
{
	effect->EndPass();
}

/**************************************
終了処理
***************************************/
void SpriteEffect::End()
{
	effect->End();
}

/**************************************
変更反映処理
***************************************/
void SpriteEffect::Commit()
{	
	effect->SetMatrix(hMtxView, &mtxView);
	effect->SetMatrix(hMtxProj, &mtxProjection);
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
	effect->SetMatrix(hMtxWorld, &mtxWorld);
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
ビュー行列設定処理
***************************************/
void SpriteEffect::SetView(const D3DXMATRIX & mtx)
{
	mtxView = mtx;
}

/**************************************
プロジェクション行列設定処理
***************************************/
void SpriteEffect::SetProjection(const D3DXMATRIX & mtx)
{
	mtxProjection = mtx;
}

/**************************************
スクリーン投影行列設定処理
***************************************/
void SpriteEffect::SetScreenProjection(const D3DXMATRIX & mtx)
{
	mtxScreenProj = mtx;
}
