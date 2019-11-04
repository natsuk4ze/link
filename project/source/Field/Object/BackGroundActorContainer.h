//=====================================
//
// BackGroundActorContainer.h
// 機能:背景アクターのコンテナ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BACKGROUNDACTORCONTAINER_H_
#define _BACKGROUNDACTORCONTAINER_H_

#include "../../../main.h"
#include <vector>

#include "../FieldConfig.h"

/**************************************
前方宣言
***************************************/
class PlaceActor;

namespace Field::Actor
{
	/**************************************
	前方宣言
	***************************************/

	/**************************************
	クラス定義	
	***************************************/
	class BackGroundActorContainer
	{
	public:
		BackGroundActorContainer(FieldLevel level);
		~BackGroundActorContainer();

		void Update();
		void Draw();

		void Load();

	private:
		FieldLevel fieldLevel;
		std::vector<PlaceActor*> groundContainer;
		std::vector<PlaceActor*> riverContainer;
	};
}
#endif