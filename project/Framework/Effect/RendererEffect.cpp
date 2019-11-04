//=====================================
//
//描画エフェクト処理[RendererEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "RendererEffect.h"

/**************************************
static変数
***************************************/
D3DXMATRIX RendererEffect::mtxView;
D3DXMATRIX RendererEffect::mtxProjection;
std::vector<D3DLIGHT9> RendererEffect::lightContainer;

/*************************************
ライト設定処理
***************************************/
void RendererEffect::SetLight(int index, const D3DLIGHT9 & light)
{
	if ((int)lightContainer.size() < index)
		lightContainer.resize(index);

	lightContainer[index] = light;
}

/*************************************
ビュー行列設定処理
***************************************/
void RendererEffect::SetView(const D3DXMATRIX & viewMatrix)
{
	mtxView = viewMatrix;
}

/*************************************
プロジェクション行列設定処理
***************************************/
void RendererEffect::SetProjection(const D3DXMATRIX & projectionMatrix)
{
	mtxProjection = projectionMatrix;
}

/**************************************
変更反映処理
***************************************/
void RendererEffect::Commit()
{
	effect->CommitChanges();
}

/**************************************
描画開始宣言
***************************************/
void RendererEffect::Begin()
{
	effect->Begin(0, 0);
}

/**************************************
パス開始宣言
***************************************/
void RendererEffect::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
パス終了宣言
***************************************/
void RendererEffect::EndPass()
{
	effect->EndPass();
}

/**************************************
描画終了宣言
***************************************/
void RendererEffect::End()
{
	effect->End();
}