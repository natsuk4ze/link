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

class FieldEventHandler;

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

		//オブジェクトの更新処理
		void UpdateObject();

		//ロジックの更新処理
		void UpdateLogic();

		//描画処理
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
		void SetCallbackOnBuildRoad(Delegate<void(std::vector<Model::PlaceModel*>&)> *callback);

		//レベルアップするべきかどうか
		bool ShouldLevelUp();

		//イベントハンドラ設定処理
		void SetEventHandler(::FieldEventHandler& handler);

	private:
		//内部クラス前方宣言
		class FieldDevelopper;
		class FieldInput;

		//static定数メンバ
		static const float PlaceOffset;					//Placeの1マス毎のオフセット値
		static const int InitFieldBorder;				//フィールド範囲の初期値
		static const int DevelopmentInterval;			//AI発展レベルが上がるインターバル
		static const float MaxDevelopmentLevelAI;		//AI発展レベルの最大値

		FieldCursor *cursor;								//カーソル
		FieldGround *ground;								//地面

		Model::PlaceContainer *placeContainer;				//プレイスコンテナ
		Model::OperatePlaceContainer *operateContainer;		//操作対象プレイスのコンテナ
		Model::RouteContainer routeContainer;				//ルートモデルコンテナ
		Model::RouteProcessor *routeProcessor;				//ルートプロセッサ
		Actor::PlaceActorController* placeActController;	//プレイスアクターコントローラ

		FieldDevelopper *developper;
		FieldInput *input;

		int fieldBorder;						//フィールド範囲(マス単位)
		int cntFrame;							//フレームカウント
		float developmentLevelAI;				//AI発展レベル
		float developSpeedBonus;				//発展スピード増加ボーナス

		State current;
		ControllerState *state;					//現在のステート
		std::vector<ControllerState*> fsm;		//ステートマシン

		//デリゲータ
		Delegate<void(const Model::PlaceModel*)> *onConnectTown;
		Delegate<void(const Model::PlaceModel*)> *onCreateJunction;
		Delegate<void(const Model::PlaceModel*)> *onChangePlaceType;
		Delegate<void(std::vector<Model::PlaceModel*>&)> *onBuildRoad;

		//ステート切り替え
		void ChangeState(State next);

		//カーソル位置のプレイスを取得
		Model::PlaceModel* GetPlace();
		
		//AI発展レベルの計算、加算
		void CalcDevelopmentLevelAI();

		//各ステートクラスの前方宣言
		class IdleState;
		class BuildRoadState;
		class UseItemState;
	};
}
#endif