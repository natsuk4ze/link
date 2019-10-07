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

class ItemModel;

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

	private:
		const float PlaceOffset = 10.0f;		//Placeの1マス毎のオフセット値
		const int InitFieldBorder = 25;			//フィールド範囲の初期値
		const int InputLongWait = 15;			//入力リピートの待機フレーム
		const int InputShortWait = 5;			//入力リピートの待機フレーム

		FieldCursor *cursor;					//カーソル
		FieldGround *ground;					//地面
		Model::PlaceContainer *placeContainer;	//プレイスコンテナ
		ItemModel* item;						// アイテムモデル

		int fieldBorder;						//フィールド範囲(マス単位)
		int inputRepeatCnt;						//入力のリピートカウント
	};
}
#endif