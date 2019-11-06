//=====================================
//
//SpaceBackGroundContainer.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SPACEBACKGROUNDCONTAINER_H_
#define _SPACEBACKGROUNDCONTAINER_H_

#include "../.././GameMain.h"
#include "BackGroundContainer.h"

/**************************************
前方宣言
***************************************/
class InstancingMeshContainer;

namespace Field::Actor
{
	/**************************************
	クラス定義
	***************************************/
	class SpaceBackGroundContainer : public BackGroundContainer
	{
	public:
		SpaceBackGroundContainer();
		~SpaceBackGroundContainer();

		void Update();
		void Draw();

		void Load();

		bool IsSeaPlace(const FieldPosition& position) const;

	private:
		InstancingMeshContainer * tearMesh;		//時空の裂け目のメッシュ
	};
}
#endif