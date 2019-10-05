//=====================================
//
//FieldPlaceModel.cpp
//機能:フィールド上のプレイスモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldPlaceModel.h"

#include "../../FieldObject/PlaceActor.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

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
		Position(x, z),
		actor(nullptr)
	{
		//隣接プレイスのコンテナを準備
		adjacencies.resize(Adjacency::Max, NULL);

		//アクターの生成
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceModel::~PlaceModel()
	{
		belongRouteList.clear();
		SAFE_DELETE(actor);
	}

	/**************************************
	更新処理
	***************************************/
	void PlaceModel::Update()
	{
		if (actor != NULL)
		{
			actor->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void PlaceModel::Draw()
	{
		if (actor != NULL)
		{
			actor->Draw();
		}

#ifdef DEBUG_PLACEMODEL
		//テスト描画
		Transform transform = Transform(
			{ Position.x * 10.0f, 1.0f, Position.z * 10.0f },
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);
		transform.SetWorld();
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon(PolygonName[type], polygon);
		polygon->Draw();
#endif
	}

	/**************************************
	座標取得処理
	***************************************/
	FieldPosition PlaceModel::GetPosition() const
	{
		return Position;
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
	bool PlaceModel::CanStartRoute()
	{
		//空白タイプか橋でなければ道に出来ない
		if(!ChangeableRoad())
			return false;

		//隣接プレイスに交差点、街、道が含まれていたらルートを始められる
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			if (adjacency->IsConnectableType())
				return true;
		}

		return false;
	}

	/**************************************
	道に変えられるか
	***************************************/
	bool PlaceModel::ChangeableRoad()
	{
		//Noneと橋のみ道にすることが出来る
		if (type == PlaceType::None)
			return true;

		if (type == PlaceType::Bridge)
			return true;

		return false;
	}

	/**************************************
	プレイスと隣接しているか
	***************************************/
	bool PlaceModel::IsAdjacent(PlaceModel * place)
	{
		//隣接プレイスの中から等しいものを検索
		auto itr = std::find_if(adjacencies.begin(), adjacencies.end(), [&](auto adjacency)
		{
			return adjacency == place;
		});

		return itr != adjacencies.end();
	}

	/**************************************
	連結可能なタイプか
	***************************************/
	bool PlaceModel::IsConnectableType()
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
	bool PlaceModel::IsSameRoute(PlaceModel * place)
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
	PlaceModel* PlaceModel::GetConnectTarget()
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
	PlaceModel* PlaceModel::GetEdgeOpponent()
	{
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			//道で同じルートに属していなければ端点として成立
			if (adjacency->IsType(PlaceType::Road) && !IsSameRoute(adjacency))
				return adjacency;

			//街か交差点なら端点として成立
			if (adjacency->IsType(PlaceType::Town) || adjacency->IsType(PlaceType::Junction))
				return adjacency;
		}
		return nullptr;
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
		if(!exceptRoute.empty())
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
	bool PlaceModel::IsType(PlaceType type)
	{
		return this->type == type;
	}

	/**************************************
	タイプセット
	***************************************/
	void PlaceModel::SetType(PlaceType type)
	{
		this->type = type;
	}

	/**************************************
	ルート取得
	***************************************/
	RouteModelPtr PlaceModel::GetConnectingRoute()
	{
		return *(belongRouteList.begin());
	}

	/**************************************
	タイプセット
	***************************************/
	RouteContainer PlaceModel::GetConnectingRoutes()
	{
		return belongRouteList;
	}
}