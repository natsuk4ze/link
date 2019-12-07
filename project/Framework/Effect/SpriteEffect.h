//=====================================
//
//SpriteEffect.h
//機能:スプライト描画用エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPRITEEFFECT_H_
#define _SPRITEEFFECT_H_

#include "../../main.h"
#include "../../Framework/Effect/RendererEffect.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SpriteEffect : public RendererEffect
{
public:
	//コンストラクタ、デストラクタ
	SpriteEffect(const D3DXVECTOR2& texDiv = { 1.0f, 1.0f });
	SpriteEffect(const char*  effectPath, const D3DXVECTOR2& texDiv = { 1.0f, 1.0f });
	virtual ~SpriteEffect();

	//変更反映処理
	virtual void Commit() override;

	//ワールド変換行列設定処理
	virtual void SetWorld(const D3DXMATRIX& mtxWorld);

	//ディフューズ設定処理
	virtual void SetDiffuse(const D3DXCOLOR& color);

	//テクスチャ分割数設定処理
	virtual void SetTextureDivine(const D3DXVECTOR2& divine);

	//テクスチャ通し番号設定処理
	virtual void SetTextureIndex(int index);

	//スクリーン投影行列設定処理
	static void SetScreenProjection(const D3DXMATRIX& mtx);
		
protected:
	D3DXCOLOR diffuse;					//ディフューズ
	D3DXVECTOR2 texDiv;					//テクスチャ分割数
	D3DXVECTOR2 texSize;				//分割したテクスチャのサイズ
	D3DXVECTOR2 uv;						//UV座標

	static D3DXMATRIX mtxScreenProj;	//スクリーン投影行列

	//シェーダへのハンドル
	D3DXHANDLE hMtxScreenProj;
	D3DXHANDLE hTexUV;
	D3DXHANDLE hDiffuse;
};
#endif