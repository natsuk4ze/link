//=====================================
//
//Viewer3D.h
//機能:2Dオブジェクトの3D表示
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _VIEWER3D_H_
#define _VIEWER3D_H_

#include "../../main.h"
#include "BillboardTransform.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class Viewer3D
{
public:
	//コンストラクタ
	//第1引数 DWORD 2DUIの幅を指定
	//第2引数 DWORD 2DUIの高さを指定
	//第3引数 D3DXVECTOR2 ワールド空間でのサイズを指定
	Viewer3D(DWORD sizeX, DWORD sizeY, const D3DXVECTOR2& worldSize);

	//デストラクタ
	virtual ~Viewer3D();

	//2D描画開始処理
	virtual void Begin2D();

	//2D描画終了処理
	virtual void End2D();

	//3D描画処理
	virtual void Draw3D();

	//ワールド座標設定処理
	virtual void SetPosition(const D3DXVECTOR3& position);

	//回転設定処理
	virtual void SetRotation(float x, float y, float z);

protected:
	//レンダーターゲット関連のメンバ
	LPDIRECT3DTEXTURE9 renderTarget;
	LPDIRECT3DSURFACE9 renderSurface;

	//元のレンダーターゲット保存用メンバ
	LPDIRECT3DSURFACE9 defaultSurface;

	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	//SRT情報
	BillboardTransform* transform;

	//頂点バッファ作成処理
	virtual void MakeVertexBuffer(const D3DXVECTOR2& size);

	//レンダーターゲット作成処理
	virtual void MakeRenderTarget(DWORD sizeX, DWORD sizeY);

};
#endif