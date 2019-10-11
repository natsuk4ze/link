//=====================================
//
// パッセンジャーアクター[PassengerActor.h]
// 機能：フィールド上を行き来するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PASSENGERACTOR_H_
#define _PASSENGERACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"

//**************************************
// 列挙子設定
//**************************************
namespace FModel = Field::Model;

//**************************************
// クラス定義
//**************************************
class PassengerActor :
	public GameObject
{
private:
	MeshContainer* mesh;

	// 定数定義
	static const D3DXVECTOR3 ActorScale;

public:
	PassengerActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~PassengerActor();

	void Update();
	void Draw();

	void ChangeMesh(const char* nextTag);	// メッシュ切り替え
	void Move();							// 移動
};

#endif
