//=====================================
//
//PlaceContainer.h
//機能:プレイスコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLACECONTAINER_H_
#define _PLACECONTAINER_H_

#include "../../../main.h"
#include "../FieldConfig.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;

	/**************************************
	クラス定義
	***************************************/
	class PlaceContainer
	{
	public:
		//コンストラクタ、デストラクタ
		PlaceContainer();
		~PlaceContainer();

		//更新処理、描画処理
		void Update();
		void Draw();

		//指定したマス目のPlaceModelを取得
		PlaceModel* GetPlace(int x, int z);
		PlaceModel* GetPlace(const FieldPosition& position);

		//CSVデータ読み込み
		void LoadCSV(const char* filePath);

		//プレイスの行と列の最大数取得
		FieldPosition GetPlaceBorder() const;

	private:
		const int PlaceMax = 10000;				//プレイスの最大数

		std::vector<PlaceModel*> placeVector;	//PlaceModelコンテナ

		int placeRowMax;						//1行あたりのプレイス最大数
		int placeColumMax;						//1列あたりのプレイス最大数

		bool initialized;						//初期化フラグ

		void MakeAdjacency();
	};
}

#endif