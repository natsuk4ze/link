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
	MeshContainer* mesh;								// メッシュコンテナ
	bool onCamera;

public:
	EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~EventActor();

	virtual void Update();
	virtual void Draw();

	void Rotate(float y);								// Y軸回転
	void SetPosition(const D3DXVECTOR3& Pos);			// 座標セット
	void SetColor(const D3DXCOLOR& Color);				// メッシュの色変更
	void ResetTransform();								// 座標、回転、大きさをリセットする
};

#endif
