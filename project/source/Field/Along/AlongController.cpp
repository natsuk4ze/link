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
#include "../../../Framework/Tool/DebugWindow.h"

namespace Field::Along
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
		Debug::Begin("Along");
		if (Debug::Button("Growth"))
		{
			for (auto&& pair : modelMap)
			{
				pair.second->CreateActor();
			}
		}
		Debug::End();

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
		AlongPosition key = AlongPosition(transform.GetPosition());

		if (modelMap.count(key) == 0)
		{
			AlongModel *model = new AlongModel(transform);
			modelMap.emplace(key, std::unique_ptr<AlongModel>(model));
		}

		modelMap[key]->SetType((AlongModel::Type)type);
	}

	/**************************************
	AlongPositionコンストラクタ
	***************************************/
	AlongPosition::AlongPosition(const D3DXVECTOR3 & position) :
		x(position.x), z(position.z)
	{
		
	}

	/**************************************
	AlongPosition < 演算子
	***************************************/
	bool AlongPosition::operator<(const AlongPosition & rhs) const
	{
		return std::tie(x, z) < std::tie(rhs.x, rhs.z);
	}
}
