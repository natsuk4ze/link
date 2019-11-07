//=====================================
//
// イベントアクター[UFOActor.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _UFOActor_H_
#define _UFOActor_H_

#include "EventActorBase.h"

//**************************************
// クラス定義
//**************************************
class UFOActor : public EventActorBase
{
private:
	D3DXVECTOR3 BaseHoverPos;
	int FrameCount;
	bool InHoverMotion;

	void HoverMotion(void);							// ホバリング運動

public:
	UFOActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~UFOActor();

	void Update() override;
	void SetHoverMotion(bool Flag);
};

#endif
