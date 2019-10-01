//=====================================
//
// プレイスアクター[PlaceActor.h]
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "Framework/Core/GameObject.h"
#include "Framework/Animation/AnimationManager.h"
#include "Framework/Renderer3D/MeshContainer.h"
#include "Framework/Math/Easing.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// プレイスアクター用基底クラス
//**************************************
class PlaceActor :
	public GameObject
{
protected:
	MeshContainer* container;					// メッシュコンテナ
	int animType;								// アニメーションの種類
	EaseType easeType;							// イージングタイプ

	virtual void PlayAnimation(int AnimType);	// アニメーション再生
	virtual void Rotate(float y);				// Y軸回転

public:
	PlaceActor(const D3DXVECTOR3& pos);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();
};

#endif
