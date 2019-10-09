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
#include "../Field/Place/PlaceConfig.h"
//**************************************
// マクロ定義
//**************************************

//**************************************
// 列挙子設定
//**************************************
namespace FModel = Field::Model;
namespace Field::Actor
{
	/**************************************
	アクターのアニメーションタイプを表す列挙子
	***************************************/
	enum AnimType
	{
		Create,
		Remove,
		AnimMax
	};
}
namespace FActor = Field::Actor;

//**************************************
// クラス定義
//**************************************
class PlaceActor :
	public GameObject
{
protected:
	// ***継承先のクラスで読み込み***
	MeshContainer* mesh;				// メッシュコンテナ
	// ******************************
	FActor::AnimType animType;			// アニメーションの種類
	bool animActive;					// アニメーション再生中フラグ

public:
	PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();

	// インターフェース
	virtual void PlayAnimation(FActor::AnimType AnimType);	// アニメーション再生（再生させるときのみ呼び出す）
	void Rotate(float y);									// Y軸回転
	void SetColor(const D3DXCOLOR& color, UINT index);		// メッシュの色変更

private:
	static const D3DXVECTOR3 ActorScale;
};

#endif
