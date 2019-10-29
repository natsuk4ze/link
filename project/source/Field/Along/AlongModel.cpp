//=====================================
//
//AlongModel.cpp
//機能:道沿いの建物のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AlongModel.h"
#include "AlongActor.h"

namespace Field::Along
{
	/**************************************
	staticメンバ
	***************************************/
	//アクター最大数
	const unsigned AlongModel::MaxActor[Type::Max] = {
		10, 7, 10, 4
	};

	//直線道のアクター座標
	const D3DXVECTOR3 AlongModel::StraightActorPosition[] = {
		{-15.0f, 0.0f, -15.0f},
		{-15.0f, 0.0f, -7.5f},
		{-15.0f, 0.0f, 0.0f},
		{-15.0f, 0.0f, 7.5f},
		{ -15.0f, 0.0f, 15.0f },
		{ 15.0f, 0.0f, -15.0f},
		{ 15.0f, 0.0f, -7.5f},
		{ 15.0f, 0.0f, 0.0f},
		{ 15.0f, 0.0f, 7.5f },
		{ 15.0f, 0.0f, 15.0f}
	};

	//T字路のアクター座標
	const D3DXVECTOR3 AlongModel::T_JunctionActorPosition[] = {
		{ -15.0f, 0.0f, 15.0f },
		{ -7.5f, 0.0f, 15.0f },
		{ 0.0f, 0.0f, 15.0f },
		{ 7.5f, 0.0f, 15.0f },
		{ 15.0f, 0.0f, 15.0f },
		{ -7.5f, 0.0f, -7.5f },
		{ 15.0f, 0.0f, -7.5f },
	};
	
	//カーブのアクター座標
	const D3DXVECTOR3 AlongModel::CurveActorPosition[] = {
		{ 15.0f, 0.0f, 0.0f },
		{ 15.0f, 0.0f, -7.5f },
		{ 15.0f, 0.0f, 15.0f },
		{ 15.0f, 0.0f, -15.0f },
		{ 15.0f, 0.0f, 7.5f },
		{ 0.0f, 0.0f, -15.0f },
		{ 7.5f, 0.0f, -15.0f },
		{ -7.5f, 0.0f, -15.0f },
		{ -15.0f, 0.0f, -15.0f },
		{ -15.0f, 0.0f, 15.0f },
	};

	//十字路のアクター座標
	const D3DXVECTOR3 AlongModel::CrossJunctionActorPosition[] = {
		{ -15.0f, 0.0f, -15.0f },
		{ -15.0f, 0.0f, 15.0f },
		{ 15.0f, 0.0f, -15.0f },
		{ 15.0f, 0.0f, 15.0f },
	};

	/**************************************
	コンストラクタ
	***************************************/
	AlongModel::AlongModel(const Transform& transform)
	{
		actorContainer.reserve(10);

		this->transform = new Transform(transform);
	}

	/**************************************
	デストラクタ
	***************************************/
	AlongModel::~AlongModel()
	{
		actorContainer.clear();
		SAFE_DELETE(transform);
	}

	/**************************************
	更新処理
	***************************************/
	void AlongModel::Update()
	{
		//アクターの更新処理
		for (auto&& actor : actorContainer)
		{
			actor->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void AlongModel::Draw()
	{
		D3DXMATRIX mtxWorld = transform->GetMatrix();

		//自身のTransformを反映させてアクターを描画
		for (auto&& actor : actorContainer)
		{
			actor->Draw(mtxWorld);
		}
	}

	/**************************************
	タイプセット処理
	***************************************/
	void AlongModel::SetType(Type type)
	{
		this->type = type;
		
		//アクターの数を調整
		if (actorContainer.size() >= MaxActor[type])
		{
			actorContainer.resize(MaxActor[type]);
		}

		//位置を調整
		for (unsigned i = 0; i < actorContainer.size(); i++)
		{
			actorContainer[i]->SetPosition(CalcActorPosition(i));
		}
	}

	/**************************************
	アクター作成処理
	***************************************/
	void AlongModel::CreateActor()
	{
		//アクターが最大数に到達していたら早期リターン
		if (actorContainer.size() >= MaxActor[type])
			return;

		D3DXVECTOR3 position = CalcActorPosition(actorContainer.size());

		//アクターを生成して追加
		AlongActor *actor = new AlongActor();
		actor->SetPosition(position);

		actorContainer.push_back(std::unique_ptr<AlongActor>(actor));
	}

	/**************************************
	アクター座標計算処理
	***************************************/
	D3DXVECTOR3 AlongModel::CalcActorPosition(int index)
	{
		if (type == Straight)
			return StraightActorPosition[index];

		if (type == T_Junction)
			return T_JunctionActorPosition[index];

		if (type == Curve)
			return CurveActorPosition[index];

		if (type == CrossJunction)
			return CrossJunctionActorPosition[index];

		return Vector3::Zero;
	}

}