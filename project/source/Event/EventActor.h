//=====================================
//
// イベントアクター[EventActor.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _EventActor_H_
#define _EventActor_H_

#include "../../Framework/Core/GameObject.h"
#include "../../Framework/Renderer3D/MeshContainer.h"


//**************************************
// クラス定義
//**************************************
class EventActor : public GameObject
{
private:
	D3DXVECTOR3 BaseHoverPos;
	MeshContainer* mesh;							// メッシュコンテナ
	int FrameCount;
	bool InHoverMotion;

	void HoverMotion(void);							// ホバリング運動
public:
	EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~EventActor();

	virtual void Update();
	virtual void Draw();

	void Rotate(float y);							// Y軸回転
	void SetPosition(const D3DXVECTOR3& Pos);		// 座標セット
	void SetHoverMotion(bool Flag);
};	

#endif
