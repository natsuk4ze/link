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
#include "../../../Framework/Tween/Tween.h"

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
		const D3DXVECTOR2 SizePin{ 4.5f, 4.5f };
		ResourceManager::Instance()->MakePolygon("PinActor", "data/TEXTURE/Field/fieldpin.png", SizePin, { 2.0f, 1.0f });
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
		CreatePin(place, BuildRoad);
		return true;
	}

	/**************************************
	プレイス追加開始処理
	***************************************/
	bool OperatePlaceContainer::BeginDevelop(PlaceModel * place)
	{
		//開発可能タイプ以外か確認
		if (place->IsDevelopableType())
			return false;

		//コンテナに追加してreturn true
		container.push_back(place);
		CreatePin(place, Develop);

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
		Adjacency adjacency = place->IsAdjacent(container.back());
		if (adjacency == Adjacency::NotAdjacenct)
			return false;

		//道に出来るか
		if (!place->ChangeableRoad(adjacency))
			return false;

		//追加してreturn true
		container.push_back(place);
		CreatePin(place, BuildRoad);

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
		if (place->IsAdjacent(container.back()) == Adjacency::NotAdjacenct)
			return false;

		//追加してreturn true
		container.push_back(place);
		CreatePin(place, Develop);

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
			actorContainer.clear();
			return false;
		}

		//最後に追加したプレイスがルートを始められるタイプでなければreturn false
		PlaceModel* last = *container.rbegin();
		if (!last->CanStartRoute())
		{
			container.clear();
			actorContainer.clear();
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
			actorContainer.clear();
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
		actorContainer.clear();
	}

	/**************************************
	コンテナ取得処理
	***************************************/
	std::vector<PlaceModel*> OperatePlaceContainer::GetPlaces()
	{
		return container;
	}

	/**************************************
	更新処理
	***************************************/
	void Field::Model::OperatePlaceContainer::Update()
	{
		for (auto&& actor : actorContainer)
		{
			actor->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void OperatePlaceContainer::Draw()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		for (auto&& actor : actorContainer)
		{
			actor->Draw();
		}
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	/**************************************
	ピンアクター作成処理
	***************************************/
	void Field::Model::OperatePlaceContainer::CreatePin(const PlaceModel * place, Mode mode)
	{
		PinActor *actor = new PinActor(place->GetPosition().ConvertToWorldPosition() + Vector3::Up * 5.0f, mode);
		actorContainer.push_back(std::unique_ptr<PinActor>(actor));
	}

	/**************************************
	PinActorコンストラクタ
	***************************************/
	PinActor::PinActor(const D3DXVECTOR3& position, OperatePlaceContainer::Mode mode)
	{
		polygon = new BoardPolygon();
		polygon->SetTexDiv({ 2.0f, 1.0f });
		polygon->SetTextureIndex(mode);
		ResourceManager::Instance()->GetPolygon("PinActor", polygon);
		Tween::Move(*this, position + Vector3::Up * 10.0f, position, 30, EaseType::OutCubic);
	}

	/**************************************
	PinActorデストラクタ
	***************************************/
	PinActor::~PinActor()
	{
		SAFE_DELETE(polygon);
	}

	/**************************************
	PinActor更新処理
	***************************************/
	void Field::Model::PinActor::Update()
	{
		transform->Rotate(10.0f, Vector3::Up);
	}

	/**************************************
	PinActor描画処理
	***************************************/
	void PinActor::Draw()
	{
		polygon->Draw(transform->GetMatrix());
	}
}