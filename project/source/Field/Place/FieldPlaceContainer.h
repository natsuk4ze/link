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
		PlaceContainer();
		~PlaceContainer();

		void Update();
		void Draw();

		PlaceModel* GetPlace(int x, int z);

		void LoadCSV(const char* filePath);

	private:
		const int PlaceRowMax = 100;			//1行あたりのプレイス最大数
		const int PlaceColumMax = 100;			//1列あたりのプレイス最大数
		const int PlaceMax = 10000;				//プレイスの最大数

		std::vector<PlaceModel*> placeVector;

		bool initialized;
	};
}

#endif