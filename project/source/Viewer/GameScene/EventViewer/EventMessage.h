
//=============================================================================
//
// イベントメッセージ処理 [EventMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_MESSAGE_H_
#define _EVENT_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include <functional>
#include <string>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;
class TextViewer;
class ViewerAnimater;

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

	//メッセージセット処理
	void SetEventMessage(const std::string &message, int &cnt);

	//再生状態取得処理
	bool GetIsPlaying(void);

private:
	BaseViewerDrawer *bg;
	TextViewer *text;
	ViewerAnimater *anim;

	//再生処理
	void Play(void);

	//アニメーションの動作を設定
	void SetAnimBehavior(void);

	//メッセージセットカウンター
	int messageSetCnt;

	//アニメーション終了
	bool SetPlayFinished(void);

	//再生中かどうか
	bool isPlaying;

	//アニメーション配列
	std::vector <std::function<void()>> animArray{ 3 };
};

#endif