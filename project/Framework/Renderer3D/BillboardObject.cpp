//=====================================
//
//ビルボードオブジェクト処理[BillboardObject.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BillboardObject.h"
#include "BillboardTransform.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BillboardObject::BillboardObject() :
	GameObject(new BillboardTransform)
{

}

/**************************************
コンストラクタ
***************************************/
BillboardObject::BillboardObject(const BillboardObject &gameObject) :
	GameObject(gameObject)
{
}

/**************************************
コンストラクタ
***************************************/
BillboardObject::BillboardObject(const BillboardTransform& transform) :
	GameObject(transform)
{

}

/**************************************
コンストラクタ
***************************************/
BillboardObject::BillboardObject(const bool & active) :
	GameObject(new BillboardTransform, active)
{

}

/**************************************
コンストラクタ
***************************************/
BillboardObject::BillboardObject(const BillboardTransform& transform, const bool & active) :
	GameObject(transform, active)
{

}
