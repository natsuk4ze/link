//=====================================
//
//AlongController.h
//機能:道沿いの情報コントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ALONGCONTROLLER_H_
#define _ALONGCONTROLLER_H_

#include "../../../main.h"

#include <map>

namespace Field
{
	/**************************************
	前方宣言
	***************************************/
	namespace Along
	{
		class AlongModel;
	}

	/**************************************
	クラス定義
	***************************************/
	class AlongController
	{
	public:
		enum RoadType
		{
			Straight,
			T_Junction,
			Curve,
			CrossJunction,
		};

		AlongController();
		~AlongController();

		void Update();
		void Draw();

		void OnReachPassenger(const D3DXVECTOR3& position);
		void OnBuildRoad(const Transform& transform, RoadType type);

	private:
		using AlongModelMap = std::map<D3DXVECTOR3, std::unique_ptr<Along::AlongModel>>;

		AlongModelMap modelMap;
	};
}


#endif