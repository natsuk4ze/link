//=============================================================================
//
// 連打ゲームビューアクラス [BeatGameViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BeatGameViewer_H_
#define _BeatGameViewer_H_

#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;


//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatGameViewer 
{
private:
	int CountFrame;
	float ExpandPercent;
	bool DrawFlag;
	std::function<void(void)> Callback;

	BaseViewerDrawer* Viewer;
	LPDIRECT3DTEXTURE9 SuccessTexture;
	LPDIRECT3DTEXTURE9 FailTexture;

	void SetVertex();
	void TextureExpand();

public:
	BeatGameViewer();
	~BeatGameViewer();
	void Update(void);
	void Draw(void);
	void DrawStart(bool IsSuccess,std::function<void(void)> Callback);
};

#endif

