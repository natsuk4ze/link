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
#include "../Object/WaterHeightController.h"

#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../../Framework/Tween/Tween.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	staticメンバ
	***************************************/
	const int OperatePlaceContainer::DurationMoveEmitter = 5;

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

		emitter = GameParticleManager::Instance()->Generate(GameParticle::RouteTrace, Vector3::Zero);
		emitter->SetActive(false);
		effectPinIndex = 0;

		onReachEmitter = std::bind(&OperatePlaceContainer::_OnReachEmitter, this);
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
	bool OperatePlaceContainer::BeginRoute(PlaceModel * place, bool isSea)
	{
		//ルートを始められるプレイスであるか確認
		if (!place->CanStartRoute())
			return false;

		SE::Play(SoundConfig::Select02, 0.5f);

		//コンテナに追加してreturn true
		container.push_back(place);
		CreatePin(place, BuildRoad, isSea);

		return true;
	}

	/**************************************
	プレイス追加開始処理
	***************************************/
	bool OperatePlaceContainer::BeginDevelop(PlaceModel * place, bool isSea)
	{
		//開発可能タイプ以外か確認
		if (place->IsDevelopableType())
			return false;

		SE::Play(SoundConfig::Select03, 0.5f);

		//コンテナに追加してreturn true
		container.push_back(place);
		CreatePin(place, Develop, isSea);

		return true;
	}

	/**************************************
	プレイス追加処理
	***************************************/
	bool OperatePlaceContainer::AddRoute(PlaceModel * place, bool isSea)
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
		CreatePin(place, BuildRoad, isSea);
		
		return true;
	}

	/**************************************
	プレイス追加処理
	***************************************/
	bool OperatePlaceContainer::AddDevelop(PlaceModel * place, bool isSea)
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
		CreatePin(place, Develop, isSea);

		return true;
	}

	/**************************************
	追加終了処理
	***************************************/
	bool OperatePlaceContainer::EndRoute()
	{
		if (container.size() == 1)
		{
			//端点がそれぞれ別のプレイスか
			std::vector<PlaceModel*> connectTarget = container.back()->GetEdgeOpponents();
			if (connectTarget.size() > 1)
				return true;
		}
		else
		{
			//最後に追加したプレイスがルートを始められるタイプでなければreturn false
			PlaceModel* last = *container.rbegin();
			if (!last->CanStartRoute())
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		return false;
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

		if (emitter != nullptr)
		{
			emitter->SetActive(false);
		}

		emitter->SetActive(false);
		effectPinIndex = 0;
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

		cntFrame = Math::WrapAround(0, 60, ++cntFrame);
		if (cntFrame == 0)
			StartEmitterMoving();
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
	void Field::Model::OperatePlaceContainer::CreatePin(const PlaceModel * place, Mode mode, bool isSea)
	{
		D3DXVECTOR3 offset = place->IsType(PlaceType::Mountain) ? Vector3::Up * 15.0f : Vector3::Up * 5.0f;
		PinActor *actor = new PinActor(place->GetPosition().ConvertToWorldPosition() + offset, mode, isSea);
		actorContainer.push_back(std::unique_ptr<PinActor>(actor));
	}

	/**************************************
	ルートエフェクト移動開始処理
	***************************************/
	void Field::Model::OperatePlaceContainer::StartEmitterMoving()
	{
		if (actorContainer.size() < 2)
			return;

		if (emitter->IsActive())
			return;

		D3DXVECTOR3 pinPosition = actorContainer[0]->GetPosition();
		emitter->SetActive(true);
		emitter->SetPosition(pinPosition);

		D3DXVECTOR3 nextPosition = actorContainer[1]->GetPosition();
		Tween::Move(*emitter, nextPosition, DurationMoveEmitter, EaseType::Linear, onReachEmitter);

		effectPinIndex = 1;
	}

	/**************************************
	エミッター到着コールバック
	***************************************/
	void Field::Model::OperatePlaceContainer::_OnReachEmitter()
	{
		effectPinIndex++;

		if (effectPinIndex < (int)actorContainer.size())
		{
			D3DXVECTOR3 position = actorContainer[effectPinIndex]->GetPosition();
			Tween::Move(*emitter, position, DurationMoveEmitter, EaseType::Linear, onReachEmitter);
		}
		else
		{
			effectPinIndex = 0;
			emitter->SetActive(false);
		}
	}

	/**************************************
	PinActorコンストラクタ
	***************************************/
	PinActor::PinActor(const D3DXVECTOR3& position, OperatePlaceContainer::Mode mode, bool isSea) :
		isSea(isSea)
	{
		polygon = new BoardPolygon();
		polygon->SetTexDiv({ 2.0f, 1.0f });
		polygon->SetTextureIndex(mode);

		ResourceManager::Instance()->GetPolygon("PinActor", polygon);

		transform->SetPosition(position);
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
		//海上だったら高さを水面に合わせる
		if (isSea)
		{
			D3DXVECTOR3 position = transform->GetPosition();
			position.y = WaterHeightController::GetHeight() + 5.0f;
			transform->SetPosition(position);
		}
		polygon->Draw(transform->GetMatrix());
	}
}