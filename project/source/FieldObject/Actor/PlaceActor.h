//=====================================
//
// プレイスアクター[PlaceActor.h]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Math/Easing.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// マクロ定義
//**************************************

//**************************************
// 列挙子設定
//**************************************
namespace FModel = Field::Model;

//**************************************
// クラス定義
//**************************************
class PlaceActor :
	public GameObject
{
public:
	/**************************************
	アクターのステートを表す列挙子
	***************************************/
	enum State
	{
		Idle,	// 待機
		Create,	// 作成
		Remove,	// 削除
		Link,	// リンクレベルが上がった
		Max
	};
	using ActorState = BaseState<PlaceActor, State>;

	PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	virtual ~PlaceActor();

	virtual State Update();
	virtual void Draw();

	// インターフェース
	void ChangeState(ActorState *next);					// アニメーション再生（再生させるときのみ呼び出す）
	void Rotate(float y);								// Y軸回転
	void SetColor(const D3DXCOLOR& color, UINT index);	// メッシュの色変更

protected:
	// ***継承先のクラスで読み込み***
	MeshContainer* mesh;				// メッシュコンテナ
	// ******************************

	ActorState *state;					// 現在のステート
	int cntState;						// ステート内での現在フレームのカウントに使用

private:
	static const D3DXVECTOR3 ActorScale;

	// ステートの前方宣言
	class IdleActorState;
	class CreateActorState;
	class RemoveActorState;
	class LinkActorState;
};

#endif
