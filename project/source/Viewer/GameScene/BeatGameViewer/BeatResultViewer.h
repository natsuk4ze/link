
//=============================================================================
//
// 連打ゲーム結果ビュアー処理 [BeatResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_RESULT_VIEWER_H_
#define _BEAT_RESULT_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BeatResultViewer :public BaseViewer
{
public:
	BeatResultViewer();
	~BeatResultViewer();

	//結果の種類
	enum ResultID
	{
		Success,
		Failed,
		Max
	};

	void Update();
	void Draw(void);
	void Set(ResultID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer * text;
	BaseViewerDrawer *bg;

	//再生終了通知
	std::function<void(void)> Callback;

	//再生
	void Play();

	//テクスチャ情報受け渡し
	void SetTexture(ResultID id);

	//背景をオープン
	void OpenBG(void);

	//背景をクローズ
	void CloseBG(void);

	//再生中かどうか
	bool isPlaying;

	//フレームカウント
	int countFrame;

	//現在のアニメーション
	int currentAnim;

	//アニメーション時間
	float animTime;
};

#endif