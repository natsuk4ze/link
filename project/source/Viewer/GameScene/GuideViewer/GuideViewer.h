//=====================================
//
// ガイドビュアー[GuideViewer.h]
// 機能：ガイド役キャラクター表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "../../../../Framework/Pattern/BaseSingleton.h"
#include "../../../../Framework/PostEffect/Effect/CRTFilter.h"
#include <string>
#include "GuideActor.h"
#include <deque>
#include "../../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class GuideCamera;
class GuideViewerBG;
class GuideCallOutViewer;
class SubScreen;

//**************************************
// クラス定義
//**************************************
struct GuideViewerData
{
	std::string message;
	GuideActor::AnimState animation;
	SE::VoiceType voice;
	GuideViewerData(std::string message, GuideActor::AnimState next, SE::VoiceType voice) {
		this->message = message;
		this->animation = next;
		this->voice = voice;
	}
};

//**************************************
// クラス定義
//**************************************
class GuideViewer :
	public BaseSingleton<GuideViewer>
{
	friend class BaseSingleton<GuideViewer>;
public:
	void Init();	// 各種インスタンスの初期化
	void Uninit();	// 各種インスタンスの削除

	void Update();
	void Draw();

	void SetActive(bool flag);

	// メッセージをセット
	void SetMessage(const std::string &message);
	// アニメーションを変更
	void ChangeAnim(GuideActor::AnimState next);

	// 上の２つ＆VOICEの再生をまとめて行う
	void SetData(const std::string& message, GuideActor::AnimState next, SE::VoiceType voice);

private:
	// 各種インスタンス用ポインタ
	GuideActor* actor;
	GuideCamera* camera;
	GuideViewerBG* bg;
	CRTFilter* filter;
	GuideCallOutViewer *callOutViewer;
	SubScreen* subScreen;

	std::deque<GuideViewerData*> que;	// アニメーション、メッセージ、SEを順番に収納するキュー
	SE::VoiceType prev;
	int cntQue;
	bool isActive;	// 描画可否判定

	static const D3DXVECTOR2 SubScreenPosition;
	static const D3DXVECTOR2 SubScreenSize;

	GuideViewer() {}
	~GuideViewer() {}

	void UpdateDeque();

};

#endif
