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

private:
	//シェーダへのハンドル
	D3DXHANDLE hTechnique;
};

#endif