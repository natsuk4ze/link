
//=============================================================================
// 
// 連打ゲームタイトルビュアー処理 [BeatTitleViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_TITLE_VIEWER_H_
#define _BEAT_TITLE_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatTitleViewer :public BaseViewer
{
public:
	BeatTitleViewer();
	~BeatTitleViewer();

	//タイトルの種類
	enum TitleID
	{
		//ボタンを連打して街を守れ！
		ProtectCity,
		//ボタンを連打してAIを鎮めろ！
		CalmAI,
		//種類数
		Max
	};

	void Update();
	void Draw(void);
	void Set(TitleID id);

private:
	BaseViewerDrawer *title;

	//テクスチャをセット
	void SetTexture(TitleID id);
};

#endif