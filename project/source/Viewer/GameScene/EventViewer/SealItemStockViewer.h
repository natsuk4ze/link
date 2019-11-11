//=============================================================================
//
// ストック封印ビュアー処理 [SealItemStockViewer.h]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#ifndef _SEAL_STOCK_VIEWER_H_
#define _SEAL_STOCK_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SealItemStockViewer :public BaseViewer
{
public:
	SealItemStockViewer();
	~SealItemStockViewer();

	void Update(void);
	void Draw(void);

	//パラメータを受けとる箱
	bool parameterBox;

private:

	//アイコン
	BaseViewerDrawer *icon;		

	//再生処理
	void Play(void);

	//封印アニメーションを再生
	void PlaySealAnim(void);

	//封印解除アニメーションを再生
	void PlayUnSealAnim(void);

	//アニメーション制御処理
	void HandlePlayAnim(void);

	//現在のパラメータ
	bool currentParam;

	//１フレーム前のパラメータ
	bool lastParam;

	//再生中かどうか
	bool isPlaying;

	//封印されたか
	bool isSealed;

	//封印が解かれたか
	bool isUnSealed;

	//アニメーション時間
	float animTime;

	//フレームカウント
	int countFrame;
};


#endif