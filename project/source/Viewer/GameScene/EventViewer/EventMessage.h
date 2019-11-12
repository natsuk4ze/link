
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

	//メッセージセット
	void SetEventMessage(const std::string &message, int &cnt);

	//メッセージセットカウンター
	int messageSetCnt;

	//再生中かどうか
	bool isPlaying;

private:
	BaseViewerDrawer *bg;
	TextViewer *text;

	//アニメーション時間
	float animTime;

	//フレームカウント
	int countFrame;

	//現在再生中のアニメーション
	int currentAnim;

	//α値
	float alpha = 1.0f;

	//再生処理
	void Play(void);

	//フェードアウト処理
	void FadeOut(void);
};

#endif