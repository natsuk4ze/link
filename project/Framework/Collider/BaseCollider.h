//=====================================
//
//ベースコライダーヘッダ[BaseCollider.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASECOLLIDER_H_
#define _BASECOLLIDER_H_

#include "../../main.h"
#include "ColliderObserver.h"
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class BaseCollider
{
public:
	BaseCollider(const std::shared_ptr<Transform> transform);
	virtual ~BaseCollider();

	void SetActive(bool state);
	bool IsActive();

	void AddObserver(ColliderObserver* observer);
	void RemoveObserver(ColliderObserver* observer);

protected:
	bool active;
	std::shared_ptr<Transform> refTransform;
	std::vector<ColliderObserver*> observers;
};

#endif