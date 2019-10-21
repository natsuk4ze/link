
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
#include "../../../../Framework/Pattern/Delegate.h"
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class TelopDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventTelop :public BaseViewer
{
public:
	//テロップの種類
	enum TelopID
	{
		PositiveEvent01,
		PositiveEvent02,
		NegativeEvent01,
		NegativeEvent02
	};

	EventTelop();
	~EventTelop();

	//テロップの種類数
	static const int typeMax = 4;

	void Update();
	void Draw(void);
	void Set(TelopID id, Delegate<void(void)> *onFinish);

private:
	TelopDrawer *text;
	TelopDrawer *bg;

	//再生終了通知
	Delegate<void(void)> *onFinish;

	//テキストのテクスチャ情報コンテナ
	std::vector <LPDIRECT3DTEXTURE9> textTexContainer;
	//背景のテクスチャ情報コンテナ
	std::vector <LPDIRECT3DTEXTURE9> bgTexContainer;

	//再生
	void Play();

	//テクスチャ情報受け渡し
	void PassTexture(TelopID id);
};

#endif