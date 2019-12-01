
//=============================================================================
//
// イベントメッセージ処理 [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include <functional>
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
	ViewerAnimater *anim;

	//再生処理
	void Play(void);

	//アニメーションの動作を設定
	void SetAnimBehavior(void);

	//アニメーション終了
	bool SetPlayFinished(void);

	//アニメーション配列
	std::vector <std::function<void()>> animArray;

};

#endif