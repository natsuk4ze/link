
//=============================================================================
//
// イベントメッセージ処理 [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventMessage :public BaseViewer
{
public:
	EventMessage();
	~EventMessage();

	void Update(void);
	void Draw(void);

	void SetEventMessage(const std::string &message);

private:
	BaseViewerDrawer *bg;
	TextViewer *text;

	//フレームカウント
	int countFrame;

	//現在再生中のアニメーション
	int currentAnim;

	//再生中かどうか
	bool isPlaying;

	//α値
	float alpha = 1.0f;

	//アニメーションさせる
	void Animate(void);

	//フェードアウトさせる
	void FadeOut(void);
};

#endif