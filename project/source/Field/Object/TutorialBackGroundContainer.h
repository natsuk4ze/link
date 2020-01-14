//=============================================================================
//
// チュートリアル用地面コンテナクラス [TutorialBackGroundContainer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TutorialBackGroundContainer_H_
#define _TutorialBackGroundContainer_H_

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
	class TutorialBackGroundContainer : public BackGroundContainer
	{
	public:
		TutorialBackGroundContainer();
		~TutorialBackGroundContainer();

		void Update();
		void Draw();

		void Load(int csvNo);

		bool EnableAtlantis(const FieldPosition& position) const;

	private:
		InstancingMeshContainer *groundMesh;
	};
}
#endif