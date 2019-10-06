//=====================================
//
//FieldController.h
//機能:フィールドコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCONTROLLER_H_
#define _FIELDCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseState.h"
#include "Place\PlaceConfig.h"

#include <vector>

class PlaceModel;

namespace Field
{
	/**************************************
	前方宣言
	***************************************/
	class FieldCursor;
	class FieldGround;
	
	namespace Model
	{
		class PlaceContainer;
		class OperatePlaceContainer;
	}

	using PlaceVector = std::vector<Model::PlaceModel*>;
	using PlaceIterator = PlaceVector::iterator;
	using ReversePlaceIterator = std::reverse_iterator<PlaceIterator>;

	/**************************************
	クラス定義
	***************************************/
	class FieldController
	{
	public:
		//フィールドコントローラのモード列挙子
		enum State
		{
			Idle,			//特に何もしない状態
			Build,			//道を作る状態
			Develop,		//アイテムを使って川、山を開拓する状態
			Max
		};

		//コンストラクタ、デストラクタ
		FieldController();
		~FieldController();

		//更新、描画処理
		void Update();
		void Draw();

		//データ読み込み処理
		//TODO:読み込むデータを選択できるようにする
		void Load();

		//入力確認処理
		void CheckInput();

		//カーソル取得処理
		GameObject* GetFieldCursor();

		typedef BaseState<FieldController, FieldController::State> ControllerState;

	private:
		static const float PlaceOffset;					//Placeの1マス毎のオフセット値
		static const int InitFieldBorder;				//フィールド範囲の初期値
		static const int InputLongWait;					//入力リピートの待機フレーム
		static const int InputShortWait;				//入力リピートの待機フレーム
		static const unsigned InitDevelopRiverStock;	//川開発ストックの初期数
		static const unsigned InitDevelopMountainStock;	//山開発ストックの初期数

		FieldCursor *cursor;								//カーソル
		FieldGround *ground;								//地面

		Model::PlaceContainer *placeContainer;				//プレイスコンテナ
		Model::OperatePlaceContainer *operateContainer;		//操作対象プレイスのコンテナ
		Model::RouteContainer routeContainer;				//ルートモデルコンテナ

		int fieldBorder;						//フィールド範囲(マス単位)
		int inputRepeatCnt;						//入力のリピートカウント
		unsigned stockDevelopRiver;				//川開発アイテムストック
		unsigned stockDevelopMountain;			//山開発アイテムストック

		State current;
		ControllerState *state;					//現在のステート
		std::vector<ControllerState*> fsm;		//ステートマシン

		//ステート切り替え
		void ChangeState(State next);

		//カーソル位置のプレイスを取得
		Model::PlaceModel* GetPlace();

		//道を作る
		void BuildRoad();

		//川、山の開発
		void DevelopPlace(PlaceVector& route, PlaceIterator start);
		PlaceIterator DevelopMountain(PlaceVector& route, PlaceIterator moutain);
		PlaceIterator DevelopRiver(PlaceVector& route, PlaceIterator river);

		//各ステートクラスの前方宣言
		class IdleState;
		class BuildRoadState;
		class UseItemState;
	};
}
#endif