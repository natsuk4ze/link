//=====================================
//
// InstancingMeshEffect.h
// 機能:メッシュインスタンシング用エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _INSTANCINGMESHEFFECT_H_
#define _INSTANCINGMESHEFFECT_H_

#include "../../main.h"
#include "RendererEffect.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class InstancingMeshEffect : public RendererEffect
{
public:
	//コンストラクタ、デストラクタ
	InstancingMeshEffect();
	~InstancingMeshEffect();

	void CommitLightAndCamera();

	//マテリアル設定処理
	void SetMaterial(const D3DMATERIAL9& material);

private:
	//シェーダへのハンドル
	D3DXHANDLE hMtxView;
	D3DXHANDLE hMtxProjection;
	
	D3DXHANDLE hMaterialDiffuse;
	D3DXHANDLE hMaterialAmbient;
	D3DXHANDLE hMaterialSpecular;

	D3DXHANDLE hLightDirection;
	D3DXHANDLE hLightDiffuse;
	D3DXHANDLE hLightAmbient;
	D3DXHANDLE hLightSpecular;

	D3DXHANDLE hTechnique;
};

#endif