//=====================================
//
// ガイドビュアー[GuideViewer.h]
// 機能：ガイド役キャラクター表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "../../../../Framework/PostEffect/Effect/CRTFilter.h"
#include "GuideActor.h"
#include "GuideCamera.h"
#include "GuideViewerBG.h"

//**************************************
// クラス定義
//**************************************
class GuideViewer
{
private:
	// 各種インスタンス用ポインタ
	GuideActor* actor;
	GuideCamera* camera;
	GuideViewerBG* bg;
	CRTFilter* filter;

	bool isActive;	// 描画可否判定

	// 描画用サブスクリーンを作成
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	LPDIRECT3DVERTEXBUFFER9 screenVtx;
	void MakeRenderTarget();
	void MakeScreen();

	static const D3DXVECTOR3 SubScreenPosition;

public:
	GuideViewer();
	~GuideViewer();

	void Update();
	void Draw();

	void ChangeAnim(GuideActor::AnimState next);
	void SetActive(bool flag);

	static const D3DXVECTOR2 SubScreenSize;

};

#endif
