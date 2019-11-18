//=====================================
//
// RendererEffect.h
// 機能:描画エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RENDEREREFFECT_H_
#define _RENDEREREFFECT_H_

#include "../../main.h"

#include <vector>

/**************************************
クラス定義
***************************************/
class RendererEffect
{
public:
	RendererEffect() {}
	virtual ~RendererEffect() {}

	//ビュー、プロジェクション行列設定処理
	static void SetView(const D3DXMATRIX& viewMatrix);
	static void SetProjection(const D3DXMATRIX& projectionMatrix);

	//ライト情報設定処理
	static void SetLight(unsigned index, const D3DLIGHT9& light);
	
	//マテリアル設定処理
	virtual void SetMaterial(const D3DMATERIAL9& material);
	
	//変更反映処理
	void Commit(); 

	//描画開始宣言、描画終了宣言
	void Begin();
	void BeginPass(DWORD pass);
	void EndPass();
	void End();

protected:
	LPD3DXEFFECT effect;

	static D3DXMATRIX mtxView;
	static D3DXMATRIX mtxProjection;

	static std::vector<D3DXVECTOR4> lightDir;
	static std::vector<D3DCOLORVALUE> lightDiffuse;
	static std::vector<D3DCOLORVALUE> lightAmbient;
	static std::vector<D3DCOLORVALUE> lightSpecular;

	D3DXHANDLE hWorld;
	D3DXHANDLE hView;
	D3DXHANDLE hProjection;

	D3DXHANDLE hMatDiffuse;
	D3DXHANDLE hMatAmbient;
	D3DXHANDLE hMatSpecular;

	D3DXHANDLE hLightDiffuse;
	D3DXHANDLE hLightAmbient;
	D3DXHANDLE hLightSpecular;
	D3DXHANDLE hLightDirection;
};

#endif