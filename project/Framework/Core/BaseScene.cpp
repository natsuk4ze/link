//=====================================
//
//基底シーン処理[BaseScene.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BaseScene.h"

/*************************************
コンストラクタ
***************************************/
BaseScene::BaseScene(LPDIRECT3DTEXTURE9 renderTexture, LPDIRECT3DSURFACE9 renderSurface) :
	renderTexture(renderTexture),
	renderSurface(renderSurface)
{
	renderTexture->AddRef();
	renderSurface->AddRef();
}

/*************************************
デストラクタ
***************************************/
BaseScene::~BaseScene()
{
	SAFE_RELEASE(renderTexture);
	SAFE_RELEASE(renderSurface);
}
