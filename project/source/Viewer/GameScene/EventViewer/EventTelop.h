
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

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class TelopDrawer;
template<class T> class DelegateBase;

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
		PositiveEvent01,
		PositiveEvent02,
		NegativeEvent01,
		NegativeEvent02
	};

	//テロップの種類数
	static const int typeMax = 4;

	void Update(void);
	void Draw(void);
	void Set(TelopID id, DelegateBase<void>* onFinish);

private:
	TelopDrawer *text[typeMax];
	TelopDrawer *bg[typeMax];

	DelegateBase<void>* onFinish;

	void Play(int i);
};

#endif