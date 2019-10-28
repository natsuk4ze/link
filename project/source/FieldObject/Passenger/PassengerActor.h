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
#include "../../../Framework/Tween/Tween.h"
#include <functional>

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
	friend class Tween;
private:
	MeshContainer* mesh;
	D3DXVECTOR3 dest;		// 目的地

	// 定数定義
	static const D3DXVECTOR3 ActorScale;
	static const D3DXVECTOR3 InitForward;

public:
	PassengerActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~PassengerActor();

	void Update();
	void Draw();

	void ChangeMesh(const char* nextTag);	// メッシュ切り替え
	void MoveDest(const D3DXVECTOR3 dest, std::function<void(void)> callback = nullptr);	// 目的地までの移動(到達したらcallbackを返す)
};

#endif
