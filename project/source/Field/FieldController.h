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
#include "../../Framework/Pattern/Delegate.h"
#include "Place\PlaceConfig.h"
#include "../Viewer/GameScene/GameViewer/GameViewerParam.h"

#include <vector>

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
		class RouteProcessor;
	}

	namespace Actor
	{
		class PlaceActorController;
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
		using ControllerState = BaseState<FieldController, FieldController::State>;

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

		//ビューワパラメータ埋め込み
		void EmbedViewerParam(GameViewerParam& param);

		//道作成時のデリゲータ設定処理
		void SetCallbackOnBuildRoad(DelegatePtr<std::vector<Model::PlaceModel*>&> callback);

		//レベルアップするべきかどうか
		bool ShouldLevelUp();

		//イベント操作用のインターフェース
		void AdjustLevelAI(float num);				//AI発展レベルを調整
		void AdjustAllLinkLevel(float num);			//街全体のリンクレベルを調整
		void AddStockItem(int num);					//ストックアイテムの数を増やす
		void SetDevelopSpeedBonus(float num);		//発展スピードへのボーナス付与
		void CreateNewTown();						//新しい街を出現させる
		void DestroyTown();							//街を破壊する
		void ReverseOperation(bool isReverse);		//操作の反転（引数 true:反転させる false:元に戻す)
		void SealUsingItem(bool isSeal);			//ストック使用封印（引数 true:封印する false:封印を解除)
		void RaiseTrafficJam(float bias);			//混雑度を上昇させる

	private:
		static const float PlaceOffset;					//Placeの1マス毎のオフセット値
		static const int InitFieldBorder;				//フィールド範囲の初期値
		static const int InputLongWait;					//入力リピートの待機フレーム
		static const int InputShortWait;				//入力リピートの待機フレーム
		static const unsigned InitDevelopRiverStock;	//川開発ストックの初期数
		static const unsigned InitDevelopMountainStock;	//山開発ストックの初期数
		static const int DevelopmentInterval;			//AI発展レベルが上がるインターバル
		static const float MaxDevelopmentLevelAI;		//AI発展レベルの最大値

		FieldCursor *cursor;								//カーソル
		FieldGround *ground;								//地面

		Model::PlaceContainer *placeContainer;				//プレイスコンテナ
		Model::OperatePlaceContainer *operateContainer;		//操作対象プレイスのコンテナ
		Model::RouteContainer routeContainer;				//ルートモデルコンテナ
		Model::RouteProcessor *routeProcessor;				//ルートプロセッサ
		Actor::PlaceActorController* placeActController;	//プレイスアクターコントローラ

		int fieldBorder;						//フィールド範囲(マス単位)
		int inputRepeatCnt;						//入力のリピートカウント
		int cntFrame;							//フレームカウント
		float developmentLevelAI;				//AI発展レベル
		unsigned stockDevelopRiver;				//川開発アイテムストック
		unsigned stockDevelopMountain;			//山開発アイテムストック
		unsigned stockEDF;						//地球防衛軍のストック
		unsigned stockInsurance;				//保険のストック
		float developSpeedBonus;				//発展スピード増加ボーナス

		State current;
		ControllerState *state;					//現在のステート
		std::vector<ControllerState*> fsm;		//ステートマシン

		//デリゲータ
		DelegatePtr<const Model::PlaceModel*> onConnectTown;
		DelegatePtr<const Model::PlaceModel*> onCreateJunction;
		DelegatePtr<const Model::PlaceModel*> onChangePlaceType;
		DelegatePtr<std::vector<Model::PlaceModel*>&> onBuildRoad;

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
		
		//AI発展レベルの計算、加算
		void CalcDevelopmentLevelAI();

		//各ステートクラスの前方宣言
		class IdleState;
		class BuildRoadState;
		class UseItemState;
	};
}
#endif