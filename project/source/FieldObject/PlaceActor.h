//=====================================
//
// プレイスアクター[PlaceActor.h]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "../../Framework/Core/GameObject.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// クラス定義
//**************************************
class PlaceActor :
	public GameObject
{
protected:
	MeshContainer* mesh;				// メッシュコンテナ

	// ***継承先のクラスで設定***
	int animType;						// アニメーションの種類
	EaseType easeType;					// イージングタイプ
	// **************************

	void PlayAnimation(int AnimType);	// アニメーション再生
	void Rotate(float y);				// Y軸回転

public:
	PlaceActor(const D3DXVECTOR3& pos);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();
};

#endif
