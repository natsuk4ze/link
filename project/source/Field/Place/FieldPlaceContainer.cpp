//=====================================
//
//PlaceContainer.cpp
//機能:プレイスコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"
#include "FieldTownModel.h"
#include "FieldJunctionModel.h"
#include "../../../Framework/String/String.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

#include <fstream>
#include <string>

#ifdef DEBUG_PLACEMODEL
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#endif

namespace Field::Model
{
	/**************************************
	グローバル変数
	***************************************/

	/**************************************
	コンストラクタ
	***************************************/
	PlaceContainer::PlaceContainer() :
		placeRowMax(0),
		placeColumMax(0),
		initialized(false),
		trafficJamRate(0.0f),
		trafficJamBias(0.0f)
	{
		placeVector.reserve(PlaceMax);

#ifdef DEBUG_PLACEMODEL
		//デバッグ表示用の板ポリゴンを作成する
		ResourceManager::Instance()->MakePolygon("None", "", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Road", "data/TEXTURE/PlaceTest/road.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Town", "data/TEXTURE/PlaceTest/town.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("River", "data/TEXTURE/PlaceTest/river.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Bridge", "data/TEXTURE/PlaceTest/Bridge.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Junction", "data/TEXTURE/PlaceTest/junction.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Mountain", "data/TEXTURE/PlaceTest/mountain.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Operate", "data/TEXTURE/PlaceTest/operate.png", { 2.0f, 2.0f });
#endif
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceContainer::~PlaceContainer()
	{
		Utility::DeleteContainer(placeVector);

		Utility::DeleteMap(townContainer);
		Utility::DeleteMap(junctionContainer);
	}

	/**************************************
	更新処理
	***************************************/
	void PlaceContainer::Update()
	{
		if (!initialized)
			return;

		//デバッグ表示
		Debug::Log("CntLinkedTown:%d", townContainer.size());
		Debug::Log("CntJunction:%d", junctionContainer.size());
		Debug::Log("TrafficJam: %f", trafficJamRate);
	}

#ifdef DEBUG_PLACEMODEL
	/**************************************
	描画処理
	***************************************/
	void PlaceContainer::DrawDebug()
	{
		if (!initialized)
			return;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		for (auto&& place : placeVector)
		{
			place->DrawDebug();
		}

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
#endif

	/**************************************
	プレイス取得処理
	***************************************/
	PlaceModel * PlaceContainer::GetPlace(int x, int z)
	{
		if (x < 0 || x >= placeRowMax)
			return nullptr;

		if (z < 0 || z >= placeColumMax)
			return nullptr;

		return placeVector[placeColumMax * z + x];
	}

	/**************************************
	プレイス取得処理
	***************************************/
	PlaceModel* PlaceContainer::GetPlace(const FieldPosition& position)
	{
		if (position.x < 0 || position.x >= placeRowMax)
			return nullptr;

		if (position.z < 0 || position.z >= placeColumMax)
			return nullptr;

		return placeVector[placeColumMax * position.z + position.x];
	}

	/**************************************
	前プレイス取得処理
	***************************************/
	std::vector<const PlaceModel*> Field::Model::PlaceContainer::GetAllPlaces() const
	{
		std::vector<const PlaceModel*> out;
		out.assign(placeVector.begin(), placeVector.end());
		return out;
	}

	/**************************************
	CSV読み込み処理
	***************************************/
	void PlaceContainer::LoadCSV(const char * filePath)
	{
		//初期化済みであればリターン
		if (initialized)
			return;
		
		//CSVファイルを読み込み
		std::ifstream stream(filePath);

		std::string line;			//CSVを1行ずつ読むバッファ
		const char Delim = ',';		//区切り文字
		int x = 0;					//PlaceのX位置
		int z = 0;					//PlaceのZ位置

		//CSVの終わりまで読み込み続ける
		while (std::getline(stream, line))
		{
			//1行分読み込んだデータを区切り文字で分割する
			std::vector<std::string> subStr;
			String::Split(subStr, line, Delim);
		
			x = 0;

			//分割したデータ毎にPlaceModelを作成
			for (auto&& str : subStr)
			{
				PlaceType type = IntToPlaceType(std::stoi(str));
				PlaceModel *place = new PlaceModel(type, x, z);
				placeVector.push_back(place);

				x++;
			}

			z++;
		}

		//コンテナの行数と列数を保存
		placeRowMax = x;
		placeColumMax = z;

		//隣接情報作成
		MakeAdjacency();

		//初期化完了
		initialized = true;
	}

	/**************************************
	行、列の最大数取得
	***************************************/
	FieldPosition Field::Model::PlaceContainer::GetPlaceBorder() const
	{
		return FieldPosition(placeRowMax, placeColumMax);
	}

	/**************************************
	街が道と繋がったときの処理
	***************************************/
	void Field::Model::PlaceContainer::OnConnectedTown(const PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//登録確認
		if (townContainer.count(placeID) == 0)
		{
			townContainer.emplace(placeID, new TownModel(place));
		}

		townContainer[placeID]->AddGate();
	}

	/**************************************
	交差点が作られたときの処理
	***************************************/
	void Field::Model::PlaceContainer::OnCreateJunction(const PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//登録確認
		if (junctionContainer.count(placeID) == 0)
		{
			junctionContainer.emplace(placeID, new JunctionModel(place));
		}
	}

	/**************************************
	リンクレベルの計算
	***************************************/
	void Field::Model::PlaceContainer::CalcLinkLevel()
	{
		for (auto&& town : townContainer)
		{
			town.second->FindLinkedTown();
		}
	}

	/**************************************
	AI発展レベル計算
	***************************************/
	float Field::Model::PlaceContainer::CalcDevelopmentLevelAI(float bonus)
	{
		float developLevel = 0.0f;
		for (auto&& town : townContainer)
		{
			developLevel += town.second->DevelopmentLevel();
		}

		return developLevel;
	}

	/**************************************
	街全体のリンクレベル増加
	***************************************/
	void Field::Model::PlaceContainer::AddAllLinkLevel(int num)
	{
		for (auto&& town : townContainer)
		{
			town.second->AddLinkLevel(num);
		}
	}

	/**************************************
	街一つのリンクレベル増加
	***************************************/
	void Field::Model::PlaceContainer::AddLinkLevel(int num)
	{
		//ランダムに選択された街にリンクレベルを足す
		//無作為に抽出するいい方法が思い浮かばなかった
		int randomIndex = Math::RandomRange(0, (int)(townContainer.size()));
		int index = 0;
		for (auto&& town : townContainer)
		{
			if (index++ != randomIndex)
				continue;

			town.second->AddLinkLevel(num);
			return;
		}
	}

	/**************************************
	混雑度増加バイアス設定処理
	***************************************/
	void Field::Model::PlaceContainer::SetTrafficjamBias(float bias)
	{
		trafficJamBias = bias;
	}

	/**************************************
	破壊対象プレイス取得処理
	***************************************/
	const PlaceModel * Field::Model::PlaceContainer::GetDestroyTarget()
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;

		auto townVector = from(placeVector)
			>> where([](auto& place)
		{
			return place->IsType(PlaceType::Town);
		})
			>> to_vector();

		int randomIndex = Math::RandomRange(0, (int)townVector.size() - 1);
		return townVector[randomIndex];
	}

	/**************************************
	街を作れるプレイス取得処理
	***************************************/
	const PlaceModel * Field::Model::PlaceContainer::GetNonePlace()
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;

		//NOTE:取り急ぎ作った。あとできれいに治す
		auto noneVector = from(placeVector)
			>> where([](auto& place)
		{
			return place->IsType(PlaceType::None);
		})
			>> to_vector();

		int randomIndex = Math::RandomRange(0, (int)(noneVector.size() - 1));
		return noneVector[randomIndex];
	}

	/**************************************
	街破壊処理
	***************************************/
	void Field::Model::PlaceContainer::DestroyTown(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);

		if (itrPlace == placeVector.end())
			return;

		PlaceModel *place = *itrPlace;

		//所属をリセット
		RouteContainer belongRoute = place->GetConnectingRoutes();
		for (auto&& route : belongRoute)
		{
			place->ExitRoute(route);
		}

		//PlaceModelをNoneタイプに変化
		(*itrPlace)->SetType(PlaceType::None);

		//TownModel削除
		SAFE_DELETE(townContainer[target->ID()]);
		townContainer.erase(target->ID());
	}

	/**************************************
	街作成
	***************************************/
	void Field::Model::PlaceContainer::CreateTown(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);

		if (itrPlace == placeVector.end())
			return;

		PlaceModel* place = *itrPlace;
		place->SetType(PlaceType::Town);
	}

	/**************************************
	隣接情報作成
	***************************************/
	void PlaceContainer::MakeAdjacency()
	{
		for (int z = 0; z < placeColumMax; z++)
		{
			for (int x = 0; x < placeColumMax; x++)
			{
				//対象のプレイスの隣接プレイスをそれぞれ取得
				PlaceModel* back = GetPlace(x, z - 1);
				PlaceModel* left = GetPlace(x - 1, z);
				PlaceModel* forward = GetPlace(x, z + 1);
				PlaceModel* right = GetPlace(x + 1, z);

				//隣接プレイス設定
				PlaceModel *place = GetPlace(x, z);
				place->AddAdjacency(back, Adjacency::Back);
				place->AddAdjacency(left, Adjacency::Left);
				place->AddAdjacency(forward, Adjacency::Forward);
				place->AddAdjacency(right, Adjacency::Right);
			}
		}
	}
}