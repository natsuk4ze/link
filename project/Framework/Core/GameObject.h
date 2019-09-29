//=====================================
//
//ゲームオブジェクトヘッダ[GameObject.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Transform.h"
#include <memory>

class Transform;
/**************************************
マクロ定義
***************************************/

/**************************************
ゲームオブジェクト基底クラス
***************************************/
class GameObject
{
	friend class Tween;
public:
	//コンストラクタ、デストラクタ
	GameObject();
	GameObject(const GameObject& gameObject);
	GameObject(const Transform& transform);
	GameObject(const bool& active);
	GameObject(const Transform& transform, const bool& active);
	GameObject(Transform* transform);
	GameObject(Transform* tranfsorm, const bool& active);
	virtual ~GameObject();

	//代入演算子
	virtual GameObject& operator=(const GameObject&);

	//アクティブ判定
	virtual bool IsActive() const;

	//アクティブ状態セット処理
	virtual void SetActive(bool active);

	//SRT情報ゲッター（なるべく使いたくない）
	virtual D3DXVECTOR3 GetPosition() const;
	virtual D3DXVECTOR3 GetRotation() const;
	virtual D3DXVECTOR3 GetScale() const;
	virtual Transform GetTransform() const;

	//SRT情報セッター（なるべく使いたくない）
	virtual void SetPosition(const D3DXVECTOR3& position);
	virtual void SetRotatition(const D3DXVECTOR3& rotation);
	virtual void SetScale(const D3DXVECTOR3& scale);
	virtual void SetTransform(const Transform& transform);

protected:
	//アクティブ状態
	bool active;

	//SRT情報
	std::shared_ptr<Transform> transform;
};

#endif