//=====================================
//
//ビルボードオブジェクトヘッダ[BillboardObject.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BILLBOARDOBJECT_H_
#define _BILLBOARDOBJECT_H_

#include "../Core/GameObject.h"
#include "BillboardTransform.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BillboardObject : public GameObject
{
public:
	//コンストラクタ、デストラクタ
	BillboardObject();
	BillboardObject(const BillboardObject& gameObject);
	BillboardObject(const BillboardTransform& transform);
	BillboardObject(const bool& active);
	BillboardObject(const BillboardTransform& transform, const bool& active);
	virtual ~BillboardObject() {}
};

#endif