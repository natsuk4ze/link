//=====================================
//
// サブスクリーン[SubScreen.cpp]
// 機能：描画用サブスクリーン作成クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _SUBSCREEN_H_
#define _SUBSCREEN_H_

#include "../../main.h"

//**************************************
// クラス定義
//**************************************
class SubScreen
{
private:
	// 描画用サブスクリーンを作成
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	LPDIRECT3DSURFACE9 oldSuface;
	LPDIRECT3DVERTEXBUFFER9 screenVtx;
	void MakeRenderTarget();
	void MakeScreen();

	D3DXVECTOR2 size;
	D3DXVECTOR2 position;
public:
	SubScreen(D3DXVECTOR2 size, D3DXVECTOR2 position);
	~SubScreen();

	void DrawBegin();
	void DrawTexture();		// ピクセルシェーダに渡すために分離
	void DrawEnd();
};

#endif