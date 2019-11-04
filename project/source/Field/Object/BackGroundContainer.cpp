//=====================================
//
//背景アクターコンテナ基底クラス処理[BaseBackGroundContainerh.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BackGroundContainer.h"

/**************************************
コンストラクタ
***************************************/
Field::Actor::BackGroundContainer::BackGroundContainer()
{
	groundContainer.reserve(2000);
	riverContainer.reserve(500);
}

/**************************************
デストラクタ
***************************************/
Field::Actor::BackGroundContainer::~BackGroundContainer()
{
	Utility::DeleteContainer(groundContainer);
	Utility::DeleteContainer(riverContainer);
}
