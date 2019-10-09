//=====================================
//
// フィールドインフォアクター[FieldInfoActor.h]
// 機能：フィールド上の情報を表示するアクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _FIELDINFOACTOR_H_
#define _FIELDINFOACTOR_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Pattern/BaseState.h"

#include <vector>

//**************************************
// クラス定義
//**************************************
class FieldInfoActor :
	public BillboardObject
{
public:
	/**************************************
	アクターの状態を表す列挙子
	***************************************/
	enum State
	{
		Idle,		// 待機
		Create,		// 作成
		Remove,		// 削除
		Connect,	// 道がつながった
		Link,		// リンクレベルが上がった
		Congestion,	// 混雑している
		Max
	};

	FieldInfoActor(const D3DXVECTOR3& pos, State state);
	~FieldInfoActor();

	void Update();
	void Draw();

	using InfoState = BaseState<FieldInfoActor, State>;
	void ChangeState(State next);	// ステートマシンの切り替え


private:
	BoardPolygon* polygon;

	// 定数定義
	static const D3DXVECTOR3 ActorScale;
	static const D3DXVECTOR2 ActorSize;

	// ステートマシン
	State current;
	InfoState* infoState;
	std::vector<InfoState*> fsm;
	
	// 各ステートクラスの前方宣言
	class IdleFieldInfoState;
	class CreateFieldInfoState;
	class RemoveFieldInfoState;
	class ConnectFieldInfoState;
	class LinkFieldInfoState;
	class CongestionFieldInfoState;

};

#endif

