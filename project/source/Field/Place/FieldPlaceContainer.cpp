//=====================================
//
//PlaceContainer.cpp
//機能:プレイスコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"
#include "../../../Framework/String/String.h"

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
		initialized(false)
	{
		placeVector.reserve(PlaceMax);

#ifdef DEBUG_PLACEMODEL
		ResourceManager::Instance()->MakePolygon("None", "", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Road", "data/TEXTURE/PlaceTest/road.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Town", "data/TEXTURE/PlaceTest/town.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("River", "data/TEXTURE/PlaceTest/river.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Bridge", "data/TEXTURE/PlaceTest/road.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Junction", "data/TEXTURE/PlaceTest/junction.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Mountain", "data/TEXTURE/PlaceTest/mountain.jpg", { 4.5f, 4.5f });
#endif
	}

	/**************************************
	デストラクタ
	***************************************/
	PlaceContainer::~PlaceContainer()
	{
		Utility::DeleteContainer(placeVector);
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