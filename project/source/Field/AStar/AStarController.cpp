//=====================================
//
//AStarController.cpp
//機能:A*アルゴリズムのコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "AStarController.h"
#include "../Place/FieldPlaceModel.h"

namespace Field::Route
{
	/**************************************
	staticメンバ
	***************************************/
	const unsigned AStarController::MaxCheckRoute = 10000;

	/**************************************
	AStarNodeコンストラクタ
	***************************************/
	AStarNode::AStarNode(const Field::Model::PlaceModel * place) :
		Position(place->GetPosition()),
		parent(nullptr),
		realCost(9999),
		heuristicCost(9999)
	{
		adjacencyList.reserve(Field::Model::Adjacency::Max);
		adjacencyList = place->GetConnectingAdjacency();
	}

	/**************************************
	AStarNodeデストラクタ
	***************************************/
	AStarNode::~AStarNode()
	{
	}

	/**************************************
	AStarNodeスコア取得処理
	***************************************/
	int AStarNode::GetScore() const
	{
		return realCost + heuristicCost;
	}

	/**************************************
	AStarNode 実コスト取得処理
	***************************************/
	int AStarNode::GetCost() const
	{
		return realCost;
	}

	/**************************************
	AStarNodeヒューリスティックコスト計算処理
	***************************************/
	void AStarNode::CalcHeuristicCost(const Field::FieldPosition & goal)
	{
		heuristicCost = (int)fabsf((float)goal.x - Position.x) + (int)fabsf((float)goal.z - Position.z);
	}

	/**************************************
	AStarNode Open処理
	***************************************/
	void AStarNode::Open(AStarNode * parent, int realCost)
	{
		this->parent = parent;
		this->realCost = realCost;
	}

	/**************************************
	AStarNode 周囲の行けるマスの座標を取得
	***************************************/
	std::vector<Field::FieldPosition> AStarNode::GetAround() const
	{
		using Field::Model::Adjacency;

		std::vector<FieldPosition> out;
		out.reserve(4);

		if (Utility::IsContain(adjacencyList, Adjacency::Back))
			out.push_back(Position + FieldPosition(0, -1));
		if (Utility::IsContain(adjacencyList, Adjacency::Forward))
			out.push_back(Position + FieldPosition(0, 1));
		if (Utility::IsContain(adjacencyList, Adjacency::Right))
			out.push_back(Position + FieldPosition(1, 0));
		if (Utility::IsContain(adjacencyList, Adjacency::Left))
			out.push_back(Position + FieldPosition(-1, 0));

		return out;
	}

	/**************************************
	AStarNode パス取得
	***************************************/
	void AStarNode::GetPath(std::deque<D3DXVECTOR3>& pathList) const
	{
		pathList.push_front(Position.ConvertToWorldPosition());

		if (parent != nullptr)
			parent->GetPath(pathList);
	}

	/**************************************
	AStarNode 変更処理
	***************************************/
	void AStarNode::Change(const Field::Model::PlaceModel * place)
	{
		//隣接情報を更新する
		adjacencyList = place->GetConnectingAdjacency();
	}

	/**************************************
	AStarControllerコンストラクタ
	***************************************/
	AStarController::AStarController()
	{
	}

	/**************************************
	デストラクタ
	***************************************/
	AStarController::~AStarController()
	{
		nodeMap.clear();
	}

	/**************************************
	ノード変更処理
	***************************************/
	void AStarController::OnChangePlace(const Field::Model::PlaceModel * place)
	{
		Field::FieldPosition key = place->GetPosition();

		if (nodeMap.count(key) == 0)
		{
			AStarNode *node = new AStarNode(place);
			nodeMap.emplace(key, std::unique_ptr<AStarNode>(node));
		}
		else
		{
			nodeMap[key]->Change(place);
		}
	}

	/**************************************
	ルート計算処理
	***************************************/
	std::deque<D3DXVECTOR3> AStarController::CalcRoute(const Field::FieldPosition &start, const Field::FieldPosition &goal)
	{
		closeList.clear();
		openList.clear();

		//ゴール地点のノードを取得
		AStarNode *goalNode = nodeMap[goal].get();

		//スタート地点のノードを取得してオープン
		AStarNode *node = nodeMap[start].get();
		node->Open(nullptr, 0);
		openList.push_back(node);

		//目標へのルート
		std::deque<D3DXVECTOR3> route;

		//試行回数を数えて、2000回超えたら強制中断
		for (int i = 0; i < 10000; ++i)
		{
			//オープンしたノードをクローズする
			CloseNode(node);

			//ノードの周囲をオープンする
			OpenAroundNode(node);

			//最小スコアのノードを検索
			node = SearchMinScoreNode(goal);

			//袋小路
			if (node == nullptr)
			{
				break;
			}
			//ゴールに到着
			else if (node == goalNode)
			{
				CloseNode(node);
				node->GetPath(route);
				break;
			}
		}

		return route;
	}

	/**************************************
	最小スコアのノード検索
	***************************************/
	AStarNode * AStarController::SearchMinScoreNode(const Field::FieldPosition& goal)
	{
		//最小スコア
		int minScore = 99999;
		
		//最小実コスト
		int minCost = 99999;

		AStarNode *minNode = nullptr;
		for (auto&& node : openList)
		{
			int score = node->GetScore();

			if (score > minScore)
			{
				continue;
			}
			if (score == minScore && node->GetCost() >= minCost)
			{
				continue;
			}

			//更新
			minScore = score;
			minCost = node->GetCost();
			minNode = node;
		}

		return minNode;
	}

	/**************************************
	周囲のノードをオープンする
	***************************************/
	void AStarController::OpenAroundNode(AStarNode * node)
	{
		using Field::FieldPosition;

		//繋がっている方向を取得
		std::vector<FieldPosition> adjacencies = node->GetAround();

		//オープン
		for (auto&& adjacency : adjacencies)
		{
			AStarNode *around = nodeMap[adjacency].get();

			if (Utility::IsContain(closeList, around))
			{
				continue;
			}

			around->Open(node, node->GetCost() + 1);
			openList.push_back(around);
		}
	}

	/**************************************
	ノードをクローズする
	***************************************/
	void AStarController::CloseNode(AStarNode * node)
	{
		openList.remove(node);
		closeList.push_back(node);
	}

}