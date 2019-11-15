
//=============================================================================
//
// フィールドエラーメッセージ処理 [FieldErrorMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_ERRO_MESSAGE_H_
#define _FIELD_ERRO_MESSAGE_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FieldErrorMessage :public BaseViewer
{
public:
	FieldErrorMessage();
	~FieldErrorMessage();

	//メッセージの種類
	enum ErroID
	{
		//街／道とつなっがていません
		NotConnection,
		//ストックが足りません
		StockShortage,
		//橋と橋は繋げられません
		BridgeConnection,
		//橋はカーブにできません
		CurveBridge,
		//種類数
		Max
	};

	void Update();
	void Draw(void);
	void Set(ErroID id);

private:

	//テキスト
	BaseViewerDrawer *text;

	//再生
	void Play();

	//テクスチャ情報受け渡し
	void SetTexture(ErroID id);

	//再生中かどうか
	bool isPlaying;

	//フレームカウント
	int countFrame;
};

#endif