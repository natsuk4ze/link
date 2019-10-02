/*************************************/
/*!
	@file BaseGame.h
	@brief ゲームのコア部分
	@author GP12B332 21 立花雄太
	@addtogroup Core_BaseGame
	@ingroup Core_BaseGame
****************************************/
#ifndef _BASEGAME_H_
#define _BASEGAME_H_

#include "../../main.h"
#include "SceneManager.h"

class Camera;

/********************************************/
/*!
@brief ゲームのコアとなる部分のクラス
@details 実際の制作ではこのクラスを継承してゲームメインを作る
*********************************************/
class BaseGame
{
public:
	/**	コンストラクタ */
	BaseGame(HINSTANCE hInstance, HWND hWnd);

	/** デストラクタ */
	virtual ~BaseGame();

	/** 更新処理 */
	virtual void Update();

	/** 描画処理 */
	virtual void Draw();

protected:
	/** シーンマネージャ */
	SceneManager* sceneManager;

	LPDIRECT3DTEXTURE9 renderTexture;	/*!< 描画領域となるテクスチャ */
	LPDIRECT3DSURFACE9 renderSurface;	/*!< 描画領域となるサーフェイス */
	LPDIRECT3DVERTEXBUFFER9 screenVtx;	/*!< 描画用頂点バッファ */

	/** 描画用頂点バッファ作成処理 */
	virtual void MakeScreen();

	/** 描画領域作成処理 */
	virtual void MakeRenderTarget();
};


#endif