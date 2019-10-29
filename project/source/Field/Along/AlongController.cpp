//=====================================
//
//AlongController.cpp
//機能:道沿いの情報コントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AlongController.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "AlongModel.h"

namespace Field
{
	/**************************************
	コンストラクタ
	***************************************/
	AlongController::AlongController()
	{
		ResourceManager::Instance()->LoadMesh("AlongActor", "data/MODEL/AlongActor/AlongActor.x");
	}

	/**************************************
	デストラクタ
	***************************************/
	AlongController::~AlongController()
	{
		modelMap.clear();
	}

	/**************************************
	更新処理
	***************************************/
	void AlongController::Update()
	{
		for (auto&& pair : modelMap)
		{
			pair.second->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void AlongController::Draw()
	{
		for (auto&& pair : modelMap)
		{
			pair.second->Draw();
		}
	}

	/**************************************
	PassengerがPlaceに到達した際の処理
	***************************************/
	void AlongController::OnReachPassenger(const D3DXVECTOR3 & position)
	{
		assert(modelMap.count(position) != 0);

		modelMap[position]->CreateActor();
	}

	/**************************************
	道や交差点が作られた時に呼ばれる処理
	***************************************/
	void AlongController::OnBuildRoad(const Transform & transform, RoadType type)
	{
		D3DXVECTOR3 position = transform.GetPosition();

		if (modelMap.count(position) == 0)
		{
			Along::AlongModel *model = new Along::AlongModel(transform);
			modelMap.emplace(position, std::unique_ptr<Along::AlongModel>(model));
		}

		modelMap[position]->SetType((Along::AlongModel::Type)type);
	}
}
