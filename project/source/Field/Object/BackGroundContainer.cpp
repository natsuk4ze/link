//=====================================
//
//背景アクターコンテナ基底クラス処理[BaseBackGroundContainerh.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BackGroundContainer.h"
#include "../../FieldObject/Actor/PlaceActor.h"

/**************************************
コンストラクタ
***************************************/
Field::Actor::BackGroundContainer::BackGroundContainer()
{

}

/**************************************
デストラクタ
***************************************/
Field::Actor::BackGroundContainer::~BackGroundContainer()
{
	Utility::DeleteContainer(groundContainer);
	Utility::DeleteContainer(riverContainer);
}

/**************************************
海判定
***************************************/
bool Field::Actor::BackGroundContainer::IsSeaPlace(const FieldPosition& position) const
{
	return false;
}
