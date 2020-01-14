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
class SkyBox;
class SpaceGrid;

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

		void Load(int csvNo);

		bool EnableAtlantis(const FieldPosition& position) const;

		static const char* SkyboxTexName[];

	private:
		InstancingMeshContainer *tearMesh;		//時空の裂け目のメッシュ
		SkyBox *skybox;
		SpaceGrid *grid;
	};
}
#endif