//=====================================
//
//PlaceContainer.cpp
//機能:プレイスコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"

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
		if (!initialized)
			return nullptr;

		if (x < 0 || x >= PlaceRowMax)
			return nullptr;

		if (z < 0 || z >= PlaceColumMax)
			return nullptr;

		return placeVector[PlaceColumMax * z + x];
	}

	/**************************************
	CSV読み込み処理
	***************************************/
	void PlaceContainer::LoadCSV(const char * filePath)
	{
		if (initialized)
			return;



		initialized = true;
	}
}