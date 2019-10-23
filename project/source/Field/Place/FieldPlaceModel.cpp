//=====================================
//
//FieldPlaceModel.cpp
//機能:フィールド上のプレイスモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldPlaceModel.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../Route/RouteProcessor.h"
#include "../../FieldObject/Actor/StraightRoadActor.h"

#include <algorithm>

/**************************************
グローバル変数
***************************************/
#ifdef DEBUG_PLACEMODEL
static const char* PolygonName[] =
{
	"None",
	"Road",
	"Town",
	"River",
	"Bridge",
	"Junction",
	"Mountain",
};

#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#endif

namespace Field::Model
{
	/**************************************
	cpplinqのusing宣言
	***************************************/
	using cpplinq::from;
	using cpplinq::union_with;
	using cpplinq::to_vector;
	using cpplinq::intersect_with;
	using cpplinq::except;
	using cpplinq::count;

	/**************************************
	staticメンバ
	***************************************/
	unsigned PlaceModel::incrementID = 0;

	/**************************************
	コンストラクタ
	***************************************/
	PlaceModel::PlaceModel(PlaceType type, int x, int z) :
		uniqueID(incrementID++),
		type(type),
		prevType(type),
		Position(x, z)
	{
		//隣接プレイスのコンテナを準備
		adjacencies.resize(Adjacency::Max, NULL);

		connectDirection.reserve(Adjacency::Max);
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceModel::~PlaceModel()
	{
		belongRouteList.clear();
	}

#ifdef DEBUG_PLACEMODEL
	/**************************************
	描画処理
	***************************************/
	void PlaceModel::DrawDebug()
	{
		if (type != PlaceType::River && type != PlaceType::Town)
			return;

		//テスト描画
		Transform transform = Transform(
			Position.ConvertToWorldPosition() + Vector3::Up,
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);
		transform.SetWorld();
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon(PolygonName[type], polygon);
		polygon->Draw();
	}
#endif

	/**************************************
	座標取得処理
	***************************************/
	FieldPosition PlaceModel::GetPosition() const
	{
		return Position;
	}

	/**************************************
	ID取得処理
	***************************************/
	unsigned PlaceModel::ID() const
	{
		return uniqueID;
	}

	/**************************************
	隣接プレイス追加
	***************************************/
	void PlaceModel::AddAdjacency(PlaceModel *adjacency, Adjacency type)
	{
		adjacencies[type] = adjacency;
	}

	/**************************************
	ルートを始められるか
	***************************************/
	bool PlaceModel::CanStartRoute() const
	{
		//空白タイプか橋でなければ道に出来ない
		if (type != PlaceType::None && type != PlaceType::Bridge)
			return false;

		//隣接プレイスに交差点、街、道が含まれていたらルートを始められる
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			if (!adjacency->IsConnectableType())
				continue;

			//橋タイプの場合、隣接方向も確認
			if (type == PlaceType::Bridge)
			{
				Adjacency adjacenctType = IsAdjacent(adjacency);
				if (Utility::IsContain(connectDirection, adjacenctType))
					return true;
			}
			//空白タイプなら無条件でtrue
			else
			{
				return true;
			}
		}

		return false;
	}

	/**************************************
	道に変えられるか
	***************************************/
	bool PlaceModel::ChangeableRoad(Adjacency prev) const
	{
		//Noneと橋のみ道にすることが出来る
		if (type == PlaceType::None)
			return true;

		//橋の場合は方向も考慮
		if (type == PlaceType::Bridge)
		{
			if (Utility::IsContain(connectDirection, prev))
				return true;
			else
				return false;
		}

		return false;
	}

	/**************************************
	開拓可能なタイプか
	***************************************/
	bool PlaceModel::IsDevelopableType() const
	{
		if (type == PlaceType::River)
			return true;

		if (type == PlaceType::Mountain)
			return true;

		return false;
	}

	/**************************************
	プレイスと隣接しているか
	***************************************/
	Adjacency PlaceModel::IsAdjacent(const PlaceModel * place) const
	{
		//隣接プレイスの中から等しいものを検索
		auto itr = std::find_if(adjacencies.begin(), adjacencies.end(), [&](auto adjacency)
		{
			return adjacency == place;
		});

		if (itr == adjacencies.end())
			return Adjacency::NotAdjacenct;

		return (Adjacency)std::distance(adjacencies.begin(), itr);
	}

	/**************************************
	連結可能なタイプか
	***************************************/
	bool PlaceModel::IsConnectableType() const
	{
		if (type == PlaceType::Road)
			return true;

		if (type == PlaceType::Junction)
			return true;

		if (type == PlaceType::Town)
			return true;

		return false;
	}

	/**************************************
	同じルートに属しているか
	***************************************/
	bool PlaceModel::IsSameRoute(PlaceModel * place) const
	{
		//相手と自分の所属リストの積集合を求める
		auto intersect = from(belongRouteList)
			>> intersect_with(from(place->belongRouteList))
			>> to_vector();

		//積集合が空でなければ同じルートに属している
		return !intersect.empty();
	}

	/**************************************
	連結相手の取得
	TODO:連結相手を複数化
	***************************************/
	PlaceModel* PlaceModel::GetConnectTarget() const
	{
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			//連結不可であればcontinue
			if (!adjacency->IsConnectableType())
				continue;

			//連結可能であってもTownは不可
			if (adjacency->IsType(PlaceType::Town))
				continue;

			//同じルートに属していなければ連結できる
			if (!IsSameRoute(adjacency))
				return adjacency;
		}

		return nullptr;
	}

	/**************************************
	端点となるプレイスの取得
	***************************************/
	PlaceModel* PlaceModel::GetEdgeOpponent() const
	{
		PlaceModel* opponent = nullptr;

		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			//街を最優先で端点とする
			if (adjacency->IsType(PlaceType::Town))
				return adjacency;

			//街か交差点なら端点として成立
			if (adjacency->IsType(PlaceType::Junction))
				opponent = adjacency;

			//道で同じルートに属していなければ端点として成立
			if (adjacency->IsType(PlaceType::Road) && !IsSameRoute(adjacency))
				opponent = adjacency;
		}

		return opponent;
	}

	/**************************************
	ルートモデルへの所属
	***************************************/
	void PlaceModel::BelongRoute(std::shared_ptr<RouteModel> route)
	{
		//重複確認
		auto itr = std::find(belongRouteList.begin(), belongRouteList.end(), route);
		if (itr == belongRouteList.end())
		{
			belongRouteList.push_back(std::shared_ptr<RouteModel>(route));
		}
	}

	/**************************************
	ルートモデルへの所属
	***************************************/
	void PlaceModel::BelongRoute(std::vector<std::shared_ptr<RouteModel>>& routes)
	{
		//重複確認(自身の所属リストとの差集合を求める)
		auto exceptRoute = from(routes)
			>> except(from(belongRouteList))
			>> to_vector();

		//差集合のコンテナを所属リストの末尾にコピーして追加
		if (!exceptRoute.empty())
			std::copy(exceptRoute.begin(), exceptRoute.end(), std::back_inserter(belongRouteList));
	}

	/**************************************
	ルートモデルから離脱
	***************************************/
	void PlaceModel::ExitRoute(std::shared_ptr<RouteModel> route)
	{
		auto itr = std::remove(belongRouteList.begin(), belongRouteList.end(), route);
		belongRouteList.erase(itr, belongRouteList.end());
	}

	/**************************************
	タイプ判定
	***************************************/
	bool PlaceModel::IsType(PlaceType type) const
	{
		return this->type == type;
	}

	/**************************************
	タイプセット
	***************************************/
	void PlaceModel::SetType(PlaceType type)
	{
		prevType = this->type;
		this->type = type;
	}

	/**************************************
	タイプ取得
	***************************************/
	const PlaceType PlaceModel::GetType() const
	{
		return type;
	}

	/**************************************
	以前のタイプ取得
	***************************************/
	const PlaceType PlaceModel::GetPrevType() const
	{
		return prevType;
	}

	/**************************************
	ルート取得
	***************************************/
	RouteModelPtr PlaceModel::GetConnectingRoute() const
	{
		return *(belongRouteList.begin());
	}

	/**************************************
	タイプセット
	***************************************/
	RouteContainer PlaceModel::GetConnectingRoutes() const
	{
		return belongRouteList;
	}

	/**************************************
	方向セット処理
	***************************************/
	void PlaceModel::AddDirection(Adjacency direction)
	{
		if (direction == Adjacency::NotAdjacenct)
			return;

		auto itr = std::find(connectDirection.begin(), connectDirection.end(), direction);
		if (itr == connectDirection.end())
			connectDirection.push_back(direction);
	}

	/**************************************
	方向セット処理
	***************************************/
	void PlaceModel::AddDirection(PlaceModel* place)
	{
		Adjacency adjacencyType = IsAdjacent(place);

		AddDirection(adjacencyType);
	}

	/**************************************
	連結方向取得処理
	***************************************/
	std::vector<Adjacency> PlaceModel::GetConnectingAdjacency() const
	{
		return connectDirection;
	}

}