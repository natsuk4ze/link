
//=============================================================================
//
// フィールドテロップ処理 [FieldTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_TELOP_H_
#define _FIELD_TELOP_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <vector>
#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FieldTelop :public BaseViewer
{
public:
	FieldTelop();
	~FieldTelop();

	//テロップの種類
	enum TelopID
	{
		City,
		Max
	};

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer *text;
	BaseViewerDrawer *line;

	//再生終了通知
	std::function<void(void)> Callback;

	//再生
	void Play();

	//線を引く
	void DrawLine(void);

	void DrawTelopText(void);

	//フェードアウト
	void FadeOut(void);

	//再生中かどうか
	bool isPlaying;

	//フレームカウント
	int countFrame;

	//現在のアニメーション
	int currentAnim;

	//テクスチャのα値
	float alpha;

	//アニメーション時間
	float animTime;
};

#endif