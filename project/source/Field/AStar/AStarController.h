//=====================================
//
//AStarController.h
//機能:A*アルゴリズムのコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ASTARCONTROLLER_H_
#define _ASTARCONTROLLER_H_

#include "../../../main.h"
#include "../Place/PlaceConfig.h"

#include <vector>
#include <map>

/**************************************
前方宣言
***************************************/
namespace Field::Model
{
	class PlaceModel;
}

namespace Field::Route
{
	/**************************************
	ノードの座標構造体
	***************************************/
	struct NodePosition
	{
		float x, z;

		//コンストラクタ
		NodePosition(const D3DXVECTOR3& position);

		//+演算子
		NodePosition operator+(const NodePosition& rhs);

		//<演算子
		bool operator < (const NodePosition& rhs);

		//ワールド座標への変換
		D3DXVECTOR3 ToWorld();
	};

	/**************************************
	AStarノードクラス
	***************************************/
	class AStarNode
	{
	public:
		//コンストラクタ、デストラクタ
		AStarNode(const Field::Model::PlaceModel* place);
		~AStarNode();

		//スコア取得
		int GetScore() const;

		//ヒューリスティックコスト計算
		void CalcHeuristicCost(const NodePosition& goal);

		//オープン処理
		void Open(AStarNode *parent, int realCost);

		//移動可能な範囲を取得
		std::vector<NodePosition> GetAround() const;

		//パス計算
		void GetPath(std::vector<const D3DXVECTOR3>& pathList) const;

	private:
		const NodePosition Position;		//ノード座標
		
		AStarNode *parent;					//親ノード

		int realScore;						//実コスト
		int heuristicCost;					//ヒューリスティックコスト

		std::vector<Field::Model::Adjacency> adjacencyList;	//隣接情報
	};

	/**************************************
	AStar管理クラス
	***************************************/
	class AStarController
	{
	public:
		//コンストラクタ、デストラクタ
		AStarController();
		~AStarController();

		//プレイスが切り替わった際のノード変更処理
		void OnChangePlace(const Field::Model::PlaceModel* place);

		//スタートからゴールへの計算処理
		std::vector<const D3DXVECTOR3> CalcRoute(const D3DXVECTOR3& start, const D3DXVECTOR3& goal);

	private:
		//ノードマップ
		std::map<NodePosition, std::unique_ptr<AStarNode>> nodeMap;

		//オープンリスト
		std::vector<const AStarNode*> openList;

		//クローズリスト
		std::vector<const AStarNode*> closeList;
	};
}

#endif