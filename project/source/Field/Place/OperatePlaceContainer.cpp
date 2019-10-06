//=====================================
//
//OperatePlaceContainer.cpp
//機能:操作対象のプレイスを格納するコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "OperatePlaceContainer.h"
#include "FieldPlaceModel.h"

#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using宣言
	***************************************/
	using cpplinq::from;
	using cpplinq::where;
	using cpplinq::count;

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
	bool OperatePlaceContainer::BeginRoute(PlaceModel * place)
	{
		//ルートを始められるプレイスであるか確認
		if (!place->CanStartRoute())
			return false;

		//コンテナに追加してreturn true
		container.push_back(place);

		return true;
	}

	/**************************************
	プレイス追加開始処理
	***************************************/
	bool OperatePlaceContainer::BeginDevelop(PlaceModel * place)
	{
		//コンテナに追加してreturn true
		container.push_back(place);

		return true;
	}

	/**************************************
	プレイス追加処理
	***************************************/
	bool OperatePlaceContainer::AddRoute(PlaceModel * place)
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
	プレイス追加処理
	***************************************/
	bool OperatePlaceContainer::AddDevelop(PlaceModel * place)
	{
		//重複確認
		auto itr = std::find(container.begin(), container.end(), place);
		if (itr != container.end())
			return false;

		//隣接判定
		if (!place->IsAdjacent(*container.rbegin()))
			return false;

		//追加してreturn true
		container.push_back(place);

		return true;
	}

	/**************************************
	追加終了処理
	***************************************/
	bool OperatePlaceContainer::EndRoute()
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
	追加終了処理
	***************************************/
	bool OperatePlaceContainer::EndDevelop()
	{
		//開拓可能タイプ以外が2つ以上含まれていなければコンテナをクリアしてreturn false
		int cntNonDevelopable = 
			from(container) >>
			where([](auto& place) { return !place->IsDevelopableType(); }) >>
			count();

		if (cntNonDevelopable < 2)
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

	/**************************************
	デバッグ表示
	***************************************/
	void OperatePlaceContainer::DrawDebug()
	{
#ifdef DEBUG_PLACEMODEL
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon("Operate", polygon);

		for (auto&& place : container)
		{
			FieldPosition position = place->GetPosition();

			Transform transform{
				{position.x * 10.0f, 5.0f, position.z * 10.0f },
				{ D3DXToRadian(90.0f), 0.0f, 0.0f },
				Vector3::One
			};

			transform.SetWorld();

			polygon->Draw();
		}
#endif
	}
}