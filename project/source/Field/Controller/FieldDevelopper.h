//=====================================
//
//FieldDevelopper.h
//機能:フィールド開発機能
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDDEVELOPPER_H_
#define _FIELDDEVELOPPER_H_

#include "../../../main.h"
#include "../FieldController.h"

/**************************************
前方宣言
***************************************/
class GameViewerParam;

namespace Field
{ 
	/**************************************
	クラス定義
	***************************************/
	class FieldController::FieldDevelopper
	{
	public:
		FieldDevelopper(FieldController* controller);
		~FieldDevelopper();

		void BuildRoad();

		void DevelopPlace(PlaceVector& route, PlaceIterator start);
		PlaceIterator DevelopMountain(PlaceVector& route, PlaceIterator mountain);
		PlaceIterator DevelopRiver(PlaceVector& route, PlaceIterator river);

		void AddStock(int num);

		void EmbedViewerParam(GameViewerParam& param);

		static const int MaxStock;
		static const int InitStock;

	private:
		FieldController *entity;

		int stockNum;
	};
}

#endif