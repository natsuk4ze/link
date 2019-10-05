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
	}

	/**************************************
	クラス定義
	***************************************/
	class FieldController
	{
	public:
		//フィールドコントローラのモード列挙子
		enum State
		{
			Idle,
			BuildRoad,
			UseItem,
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
		const float PlaceOffset = 10.0f;		//Placeの1マス毎のオフセット値
		const int InitFieldBorder = 30;			//フィールド範囲の初期値
		const int InputLongWait = 15;			//入力リピートの待機フレーム
		const int InputShortWait = 5;			//入力リピートの待機フレーム

		FieldCursor *cursor;					//カーソル
		FieldGround *ground;					//地面
		Model::PlaceContainer *placeContainer;	//プレイスコンテナ

		int fieldBorder;						//フィールド範囲(マス単位)
		int inputRepeatCnt;						//入力のリピートカウント

		ControllerState *state;						//現在のステート
		std::vector<ControllerState*> fsm;			//ステートマシン

		//ステート切り替え
		void ChangeState(State next);

		//各ステートクラスの前方宣言
		class IdleState;
		class BuildRoadState;
		class UseItemState;
	};
}
#endif