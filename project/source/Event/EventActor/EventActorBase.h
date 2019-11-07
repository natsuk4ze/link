//=====================================
//
// イベントアクター基底クラス[EventActorBase.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _EventActorBase_H_
#define _EventActorBase_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"


//**************************************
// クラス定義
//**************************************
class EventActorBase : public GameObject
{
private:
	MeshContainer* mesh;		// メッシュコンテナ

public:
	EventActorBase(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~EventActorBase();

	virtual void Update();
	virtual void Draw();
};

#endif
