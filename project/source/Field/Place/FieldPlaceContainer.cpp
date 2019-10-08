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
		initialized(false)
	{
		placeVector.reserve(PlaceMax);

#ifdef DEBUG_PLACEMODEL
		//デバッグ表示用の板ポリゴンを作成する
		ResourceManager::Instance()->MakePolygon("None", "", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Road", "data/TEXTURE/PlaceTest/road.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Town", "data/TEXTURE/PlaceTest/town.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("River", "data/TEXTURE/PlaceTest/river.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Bridge", "data/TEXTURE/PlaceTest/Bridge.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Junction", "data/TEXTURE/PlaceTest/junction.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Mountain", "data/TEXTURE/PlaceTest/mountain.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Operate", "data/TEXTURE/PlaceTest/operate.jpg", { 2.0f, 2.0f });
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

		for (auto&& place : placeVector)
		{
			place->Update();
		}

		//デバッグ表示
		Debug::Log("CntLinkedTown:%d", townContainer.size());
		Debug::Log("CntJunction:%d", junctionContainer.size());
		Debug::Log("TrafficJam: %f", CaclTrafficJamRate());

	}

	/**************************************
	描画処理
	***************************************/
	void PlaceContainer::Draw()
	{
		if (!initialized)
			return;

		for (auto&& place : placeVector)
		{
			place->Draw();
		}
	}

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
	void Field::Model::PlaceContainer::OnConnectedTown(PlaceModel * place)
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
	void Field::Model::PlaceContainer::OnCreateJunction(PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//登録確認
		if (junctionContainer.count(placeID) == 0)
		{
			junctionContainer.emplace(placeID, new JunctionModel(place));
		}
	}

	/**************************************
	混雑度計算
	***************************************/
	float Field::Model::PlaceContainer::CaclTrafficJamRate()
	{
		//出口がある街がなければ計算が成立しないので早期リターン
		if (townContainer.empty())
			return 1.0f;

		int sumGate = 0;
		for (auto&& town : townContainer)
		{
			sumGate += town.second->GateNum();
		}

		//交差点が無い場合の計算式
		if (junctionContainer.empty())
		{
			return ((float)townContainer.size() / sumGate);
		}
		//交差点がある場合の計算式
		else
		{
			float sumTrafficJam = 0.0f;
			int validJunctionNum = 0;

			for (auto&& junction : junctionContainer)
			{
				float trafficJam = junction.second->TrafficJam(townContainer);

				if (trafficJam == 0.0f)
					continue;

				sumTrafficJam += trafficJam;
				validJunctionNum++;
			}

			return Math::Min(sumTrafficJam * 0.01f * 1.5f / (validJunctionNum * sumGate), 1.0f);
		}
	}

	/**************************************
	AI発展レベル計算
	***************************************/
	float Field::Model::PlaceContainer::CalcDevelopmentLevelAI()
	{
		float trafficJamRate = CaclTrafficJamRate();

		float developLevel = 0.0f;
		for (auto&& town : townContainer)
		{
			developLevel += town.second->OnGrowth(1.0f - trafficJamRate);
		}

		return developLevel;
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