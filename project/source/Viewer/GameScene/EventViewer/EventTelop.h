
//=============================================================================
//
// イベントテロップ処理 [EventTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_TELOP_H_
#define _EVENT_TELOP_H_

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
class EventTelop :public BaseViewer
{
public:
	EventTelop();
	~EventTelop();

	//テロップの種類
	enum TelopID
	{
		//シンギュラリティ到達！！
		Singularity,
		//アトランティス登場！！
		Atlantis,
		//新惑星を発見！！
		NewPlanet,
		//隕石が接近中！！
		Meteorite,
		//宇宙人が襲来！！
		Alien,
		//AIストライキ発生！！
		AI_Strike,
		//種類数
		Max
	};

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer *text;
	BaseViewerDrawer *bg;

	//再生終了通知
	std::function<void(void)> Callback;

	//再生
	void Play();

	//テクスチャ情報受け渡し
	void PassTexture(TelopID id);

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