//=====================================
//
//ゲームオブジェクト処理[GameObject.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameObject.h"
#include "Transform.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject() :
	transform(std::make_shared<Transform>()),
	active(true)
{

}

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject(const GameObject& gameObject) :
	transform(std::make_shared<Transform>(*gameObject.transform)),
	active(true)
{
	
}

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject(const Transform& transform) :
	transform(std::make_shared<Transform>(transform)),
	active(true)
{

}

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject(const bool& active) :
	transform(std::make_shared<Transform>()),
	active(active)
{

}

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject(const Transform& transform, const bool& active) :
	transform(std::make_shared<Transform>(transform)),
	active(active)
{

}

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject(Transform * transform) :
	active(true)
{
	this->transform.reset(transform);
}

/**************************************
コンストラクタ
***************************************/
GameObject::GameObject(Transform* transform, const bool & active) :
	active(active)
{
	this->transform.reset(transform);
}

/**************************************
代入演算子
***************************************/
GameObject& GameObject::operator=(const GameObject& other)
{
	std::shared_ptr<Transform> sptr = transform;
	transform.reset();

	transform = std::make_shared<Transform>(*other.transform);
	return *this;
}

/**************************************
デストラクタ
***************************************/
GameObject::~GameObject()
{
	transform.reset();
}

/**************************************
アクティブ判定
***************************************/
bool GameObject::IsActive() const 
{
	return active;
}

/**************************************
アクティブ状態セット処理
***************************************/
void GameObject::SetActive(bool active)
{
	this->active = active;
}

/**************************************
座標セット
***************************************/
D3DXVECTOR3 GameObject::GetPosition() const
{
	return transform->GetPosition();
}
/**************************************
座標ゲット
***************************************/
void GameObject::SetPosition(const D3DXVECTOR3& position)
{
	transform->SetPosition(position);
}

/**************************************
回転角度ゲット
***************************************/
D3DXVECTOR3 GameObject::GetRotation() const
{
	return transform->GetEulerAngle();
}

/**************************************
回転角度セット
***************************************/
void GameObject::SetRotatition(const D3DXVECTOR3& rotation)
{
	transform->SetRotation(rotation);
}

/**************************************
スケールゲット
***************************************/
D3DXVECTOR3 GameObject::GetScale() const
{
	return transform->GetScale();
}

/**************************************
スケールセット
***************************************/
void GameObject::SetScale(const D3DXVECTOR3& scale)
{
	transform->SetScale(scale);
}

/**************************************
SRT情報ゲット
***************************************/
Transform GameObject::GetTransform() const
{
	return *transform;
}

/**************************************
スケール情報ゲット
***************************************/
void GameObject::SetTransform(const Transform& transform)
{
	*this->transform = transform;
}