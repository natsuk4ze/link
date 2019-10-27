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

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class SpriteEffect
{
public:
	//コンストラクタ、デストラクタ
	SpriteEffect(const D3DXVECTOR2& texDiv = { 1.0f, 1.0f });
	~SpriteEffect();

	//描画開始、終了宣言
	void Begin();
	void BeginPass(DWORD pass);
	void EndPass();
	void End();

	//変更反映処理
	void Commit();

	//ワールド変換行列設定処理
	void SetWorld(const D3DXMATRIX& mtxWorld);

	//ディフューズ設定処理
	void SetDiffuse(const D3DXCOLOR& color);

	//テクスチャ通し番号設定処理
	void SetTextureIndex(int index);

	//ビュー行列設定処理
	static void SetView(const D3DXMATRIX& mtx);

	//プロジェクション行列設定処理
	static void SetProjection(const D3DXMATRIX& mtx);

	//スクリーン投影行列設定処理
	static void SetScreenProjection(const D3DXMATRIX& mtx);
		
private:
	LPD3DXEFFECT effect;				//シェーダエフェクト

	D3DXCOLOR diffuse;					//ディフューズ
	D3DXVECTOR2 texDiv;					//テクスチャ分割数
	D3DXVECTOR2 texSize;				//分割したテクスチャのサイズ

	static D3DXMATRIX mtxView;			//ビュー行列
	static D3DXMATRIX mtxProjection;	//プロジェクション行列
	static D3DXMATRIX mtxScreenProj;	//スクリーン投影行列

	//シェーダへのハンドル
	D3DXHANDLE hMtxWorld;				
	D3DXHANDLE hMtxView;
	D3DXHANDLE hMtxProj;
	D3DXHANDLE hMtxScreenProj;
	D3DXHANDLE hTexUV;
	D3DXHANDLE hDiffuse;
};
#endif