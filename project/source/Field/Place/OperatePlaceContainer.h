//=====================================
//
//OperatePlaceContainer.h
//機能:操作するプレイスを格納するコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _OPERATEPLACECONTAINER_H_
#define _OPERATEPLACECONTAINER_H_

#include "../../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class BoardPolygon;

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;
	class PinActor;

	/**************************************
	クラス定義
	***************************************/
	class OperatePlaceContainer
	{
	public:
		//コンストラクタ、デストラクタ
		OperatePlaceContainer();
		~OperatePlaceContainer();

		//プレイス追加開始処理
		bool BeginRoute(PlaceModel* place);
		bool BeginDevelop(PlaceModel* place);

		//プレイス追加処理
		bool AddRoute(PlaceModel* place);
		bool AddDevelop(PlaceModel* place);

		//プレイス追加終了処理
		bool EndRoute();
		bool EndDevelop();

		//コンテナクリア処理
		void Clear();

		//コンテナ取得処理
		std::vector<PlaceModel*> GetPlaces();

		//デバッグ表示
		void DrawDebug();

	private:
		std::vector<PlaceModel*> container;		//PlaceModelコンテナ
	};

	/**************************************
	ピンアクタークラス
	***************************************/
	class PinActor : GameObject
	{
	public:
		PinActor(const D3DXVECTOR3& position);
		~PinActor();

		void Draw();

	private:
		BoardPolygon *polygon;
	};
}
#endif