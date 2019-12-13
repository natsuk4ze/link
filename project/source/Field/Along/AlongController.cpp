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
#include "../../../Framework/Tween/Tween.h"

namespace Field::Along
{
	/**************************************
	コンストラクタ
	***************************************/
	AlongController::AlongController(FieldLevel level) :
		currentLevel(level)
	{

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
		//Debug::Begin("Along");
		//if (Debug::Button("Growth"))
		//{
		//	for (auto&& pair : modelMap)
		//	{
		//		pair.second->CreateActor();
		//	}
		//}
		//Debug::End();

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
		//一旦コメントアウト
		//assert(modelMap.count(position) != 0);

		if (modelMap.count(position) == 0)
			return;

		modelMap[position]->CreateActor();
		addBuildBonus();
	}

	/**************************************
	道や交差点が作られた時に呼ばれる処理
	***************************************/
	void AlongController::OnBuildRoad(const Transform & transform, RoadType type, bool onWater)
	{
		AlongPosition key = AlongPosition(transform.GetPosition());

		if (modelMap.count(key) == 0)
		{
			AlongModel *model = new AlongModel(currentLevel, onWater);
			modelMap.emplace(key, std::unique_ptr<AlongModel>(model));
		}

		modelMap[key]->SetType((AlongModel::Type)type);
		modelMap[key]->SetTransform(transform);
	}

	/**************************************
	道沿いが栄えた際のボーナス処理
	***************************************/
	void AlongController::SetBuildBonusFunc(const std::function<void()>& functor)
	{
		addBuildBonus = functor;
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
