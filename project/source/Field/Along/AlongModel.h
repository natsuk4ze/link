//=====================================
//
//AlongModel.h
//機能:道沿いの建物のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ALONGMODEL_H_
#define _ALONGMODEL_H_

#include "../../../main.h"

#include <vector>

namespace Field::Along
{
	/**************************************
	前方宣言
	***************************************/
	class AlongActor;

	/**************************************
	クラス定義
	***************************************/
	class AlongModel
	{
	public:
		//道タイプ
		enum Type
		{
			Straight,
			T_Junction,
			Curve,
			CrossJunction,
			Max
		};

		//コンストラクタ、デストラクタ
		AlongModel(const Transform& transform);
		~AlongModel();

		//更新処理、描画処理
		void Update();
		void Draw();

		//道タイプ切り替え処理
		void SetType(Type type);

		//アクター作成処理
		void CreateActor();
	
	private:
		static const unsigned MaxActor[];							//アクター最大数
		static const D3DXVECTOR3 StraightActorPosition[];			//直線道のアクター座標
		static const D3DXVECTOR3 T_JunctionActorPosition[];			//T字路のアクター座標
		static const D3DXVECTOR3 CurveActorPosition[];				//カーブのアクター座標
		static const D3DXVECTOR3 CrossJunctionActorPosition[];		//十字路のアクター座標

		std::vector<std::unique_ptr<AlongActor>> actorContainer;	//アクターコンテナ
		Transform *transform;										//自身のTransform
		Type type;													//道タイプ

		D3DXVECTOR3 CalcActorPosition(int index);					//アクター座標計算処理
	};
}

#endif