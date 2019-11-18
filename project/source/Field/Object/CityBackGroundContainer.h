//=====================================
//
// CityBackGroundContainer.h
// 機能:背景アクターのコンテナ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CITYBACKGROUNDCONTAINER_H_
#define _CITYBACKGROUNDCONTAINER_H_

#include "../../../main.h"
#include "BackGroundContainer.h"

#include <vector>
#include <map>

#include "../FieldConfig.h"

/**************************************
前方宣言
***************************************/
class PlaceActor;
class InstancingMeshContainer;

namespace Field::Actor
{
	/**************************************
	前方宣言
	***************************************/

	/**************************************
	クラス定義	
	***************************************/
	class CityBackGroundContainer : public BackGroundContainer
	{
	public:
		CityBackGroundContainer();
		~CityBackGroundContainer();

		void Update();
		void Draw();

		void Load();

		bool EnableAtlantis(const FieldPosition& position) const;

	private:
		InstancingMeshContainer *groundMesh;

		std::map<FieldPosition, int> LoadRiverFlowData();
	};
}
#endif