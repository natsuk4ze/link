
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
	std::function<void(void)> Callback = nullptr;

	//テクスチャUVセット処理
	void SetTexture(TelopID id);

	//アニメーションの動作を設定
	void SetAnimBehavior(void);

	//アニメーション終了
    bool SetPlayFinished(void);

	//再生中かどうか
	bool isPlaying;

	//アニメーション配列
	std::vector <std::function<void()>> animArray;
};

#endif