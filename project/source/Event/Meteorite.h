//=============================================================================
//
// 隕石イベントクラス [Meteorite.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _METEORITE_H_
#define _METEORITE_H_

#include "EventBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Meteorite : public EventBase
{
private:
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 GoalPos;
	D3DXVECTOR3 FallDirection;
	static LPDIRECT3DDEVICE9 Device;
	static LPD3DXMESH SphereMesh;
	static D3DMATERIAL9 Material;

public:
	Meteorite(D3DXVECTOR3 GoalPos);
	~Meteorite();
	void Update(void) override;
	void Draw(void) override;
};

#endif
