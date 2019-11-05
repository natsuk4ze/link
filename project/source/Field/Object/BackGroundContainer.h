//=====================================
//
// BaseBackGroundContainer.h
// 機能:背景アクターコンテナ基底クラス
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEBACKGROUNDCONTAINER_H_
#define _BASEBACKGROUNDCONTAINER_H_

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
	クラス定義
	***************************************/
	class BackGroundContainer
	{
	public:
		BackGroundContainer();
		virtual ~BackGroundContainer();

		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void Load() = 0;

	protected:
		std::vector<PlaceActor*> groundContainer;
		std::vector<PlaceActor*> riverContainer;
	};

}
#endif