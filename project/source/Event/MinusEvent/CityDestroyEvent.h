//=============================================================================
//
// 町消滅イベントクラス [CityDestroyEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _CityDestroyEvent_H_
#define _CityDestroyEvent_H_

#include "../EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CityDestroyEvent : public EventBase
{
private:
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 GoalPos;
	D3DXVECTOR3 FallDirection;
	static LPDIRECT3DDEVICE9 Device;
	static LPD3DXMESH SphereMesh;
	static D3DMATERIAL9 Material;

public:
	CityDestroyEvent(int FieldLevel, D3DXVECTOR3 GoalPos);
	~CityDestroyEvent();
	void Update(void) override;
	void Draw(void) override;
	std::string GetEventMessage(int FieldLevel) override;
};

#endif
