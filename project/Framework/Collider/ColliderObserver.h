//=====================================
//
//コライダーオブザーバーヘッダ[ColliderObserver.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

#include <string>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ColliderObserver
{
public:
	virtual void OnColliderHit(const std::string& other) = 0;
};

#endif