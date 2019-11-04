
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
#include <vector>
#include <functional>

//テロップの種類
enum TelopID
{
	PositiveEvent01,
	PositiveEvent02,
	NegativeEvent01,
	NegativeEvent02
};

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

	//テロップの種類数
	static const int typeMax = 4;

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer *text;
	BaseViewerDrawer *bg;

	//再生終了通知
	std::function<void(void)> Callback;

	//テキストのテクスチャ情報コンテナ
	std::vector <LPDIRECT3DTEXTURE9> textTexContainer;

	//背景のテクスチャ情報コンテナ
	std::vector <LPDIRECT3DTEXTURE9> bgTexContainer;

	//再生
	void Play();

	//テクスチャ情報受け渡し
	void PassTexture(TelopID id);

	//背景をオープン
	void OpenBG(void);

	//背景をクローズ
	void CloseBG(void);

	//背景のアクティブパーセンテージ
	float percentageBG;

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