//=====================================
//
//OperatePlaceContainer.cpp
//機能:操作対象のプレイスを格納するコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "OperatePlaceContainer.h"
#include "FieldPlaceModel.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/

	/**************************************
	コンストラクタ
	***************************************/
	OperatePlaceContainer::OperatePlaceContainer()
	{
	}

	/**************************************
	デストラクタ
	***************************************/
	OperatePlaceContainer::~OperatePlaceContainer()
	{
		container.clear();
	}

	/**************************************
	プレイス追加開始処理
	***************************************/
	bool OperatePlaceContainer::Begin(PlaceModel * place)
	{
		//ルートを始められるプレイスであるか確認
		if (!place->CanStartRoute())
			return false;

		//コンテナに追加してreturn true
		container.push_back(place);

		return true;
	}

	/**************************************
	プレイス追加処理
	***************************************/
	bool OperatePlaceContainer::Add(PlaceModel * place)
	{
		//重複確認
		auto itr = std::find(container.begin(), container.end(), place);
		if (itr != container.end())
			return false;

		//隣接判定
		if (!place->IsAdjacent(*container.rbegin()))
			return false;

		//道に出来るか
		if (!place->ChangeableRoad())
			return false;

		//追加してreturn true
		container.push_back(place);

		return true;
	}

	/**************************************
	追加終了処理
	***************************************/
	bool OperatePlaceContainer::End()
	{
		//ルートが成立するプレイスの数
		const int validContainerSize = 2;

		//プレイスが足りていなければコンテナをクリアしてreturn false
		if (container.size() < validContainerSize)
		{
			container.clear();
			return false;
		}

		//最後に追加したプレイスがルートを始められるタイプでなければreturn false
		PlaceModel* last = *container.rbegin();
		if (!last->CanStartRoute())
		{
			container.clear();
			return false;
		}

		return true;
	}

	/**************************************
	コンテナクリア処理
	***************************************/
	void OperatePlaceContainer::Clear()
	{
		container.clear();
		std::vector<PlaceModel*>().swap(container);
	}

	/**************************************
	コンテナ取得処理
	***************************************/
	std::vector<PlaceModel*> OperatePlaceContainer::GetPlaces()
	{
		return container;
	}
}