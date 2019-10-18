//=============================================================================
//
// ストック使用不可イベントクラス [BanStockUseEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BanStockUseEvent_H_
#define _BanStockUseEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BanStockUseEvent : public EventBase
{
private:
public:
	BanStockUseEvent();
	~BanStockUseEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
};

#endif
