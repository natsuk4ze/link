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
#include "../FieldConfig.h"

#include <vector>
#include <deque>
#include <map>
#include <list>

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

		//実コスト取得
		int GetCost() const;

		//ヒューリスティックコスト計算
		void CalcHeuristicCost(const Field::FieldPosition& goal);

		//オープン処理
		void Open(AStarNode *parent, int realCost);

		//移動可能な範囲を取得
		std::vector<Field::FieldPosition> GetAround() const;

		//パス計算
		void GetPath(std::deque<D3DXVECTOR3>& pathList) const;

		//変更
		void Change(const Field::Model::PlaceModel *place);

	private:
		const FieldPosition Position;		//ノード座標
		
		AStarNode *parent;					//親ノード

		int realCost;						//実コスト
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
		std::deque<D3DXVECTOR3> CalcRoute(const Field::FieldPosition& start, const Field::FieldPosition& goal, const Field::FieldPosition& town);

		static const unsigned MaxCheckRoute;

	private:
		//ノードマップ
		std::map<FieldPosition, std::unique_ptr<AStarNode>> nodeMap;

		//オープンリスト
		std::list<AStarNode*> openList;

		//クローズリスト
		std::list<AStarNode*> closeList;

		//最小スコアのノード取得
		AStarNode* SearchMinScoreNode(const Field::FieldPosition& goal);

		//ノードの周囲のマスをオープンする
		void OpenAroundNode(AStarNode* node);

		//ノードをクローズする
		void CloseNode(AStarNode* node);
	};
}

#endif