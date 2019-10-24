//=============================================================================
//
// 町消滅イベントクラス [CityDestroyEvent.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _CityDestroyEvent_H_
#define _CityDestroyEvent_H_

#include "../EventBase.h"
#include "../../Field/Place/FieldPlaceModel.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class EventViewer;
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CityDestroyEvent : public EventBase
{
private:
	D3DXVECTOR3 MeteoritePos;
	D3DXVECTOR3 MissilePos;
	D3DXVECTOR3 TownPos;
	D3DXVECTOR3 MoveDirection;
	int RemainFrame;
	bool TelopOver;
	bool CountOver;
	bool UseEDF;
	const Field::Model::PlaceModel* DestroyTown;

	//小数点
	BaseViewerDrawer *point;
	//少数部
	CountViewerDrawer *fewNum;
	//整数部
	CountViewerDrawer *intNum;

#if _DEBUG
	static LPD3DXMESH SphereMesh;
	static LPD3DXMESH MissileMesh;
	static D3DMATERIAL9 Material;
#endif

public:
	CityDestroyEvent(EventViewer* eventViewer);
	~CityDestroyEvent();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	// 隕石が来るまでのカウントダウン
	void CountdownStart(void);
	void UseMissile(bool Flag);
};

#endif
