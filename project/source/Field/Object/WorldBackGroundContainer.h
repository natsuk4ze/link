//=====================================
//
//WorldBackGroundContainer.h
//機能:ワールドレベルの背景コンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WORLDBACKGROUNDCONTAINER_H_
#define _WORLDBACKGROUNDCONTAINER_H_

#include "../../../main.h"
#include "BackGroundContainer.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class PlaceActor;
class InstancingMeshContainer;

namespace Field::Actor
{
	/**************************************
	クラス定義
	***************************************/
	class WorldBackGroundContainer : public BackGroundContainer
	{
	public:
		WorldBackGroundContainer();
		~WorldBackGroundContainer();

		void Update();
		void Draw();

		void Load(int csvNo);

		bool IsSeaPlace(const FieldPosition& position) const;

		bool EnableAtlantis(const FieldPosition& position) const;

		void CreateAtlantis(const FieldPosition& position);

	private:
		InstancingMeshContainer *groundMesh;
		InstancingMeshContainer *seaMesh;

		std::vector<FieldPosition> seaMap;
	};
}
#endif