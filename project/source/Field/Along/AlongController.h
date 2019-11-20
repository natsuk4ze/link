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
#include "../FieldConfig.h"

#include <map>
#include <functional>

namespace Field::Along
{
	/**************************************
	前方宣言
	***************************************/
	class AlongModel;

	/**************************************
	AlongPosition構造体
	***************************************/
	struct AlongPosition
	{
		AlongPosition(const D3DXVECTOR3& position);
		bool operator<(const AlongPosition& rhs) const;

		float x, z;
	};

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

		AlongController(FieldLevel level);
		~AlongController();

		void Update();
		void Draw();

		void OnReachPassenger(const D3DXVECTOR3& position);
		void OnBuildRoad(const Transform& transform, RoadType type, bool onWater);

		void SetBuildBonusFunc(const std::function<void()>& functor);

	private:
		using AlongModelMap = std::map<AlongPosition, std::unique_ptr<Along::AlongModel>>;

		AlongModelMap modelMap;

		FieldLevel currentLevel;

		std::function<void(void)> addBuildBonus;
	};
}


#endif