//=====================================
//
//トランスフォームヘッダ[Transform.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../main.h"
#include "../Math/Quaternion.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Transform
{
public:
	//コンストラクタ
	Transform();
	Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
	Transform(const Transform&);
	virtual ~Transform() {}

	//演算子
	virtual Transform operator = (const Transform&);

	//移動処理
	virtual void Move(const D3DXVECTOR3& velocity);
	virtual void SetPosition(const D3DXVECTOR3& position);
	virtual D3DXVECTOR3 GetPosition() const;

	//回転処理
	virtual void Rotate(float degreeX, float degreeY, float degreeZ);
	virtual void Rotate(float degree, const D3DXVECTOR3& axis);
	virtual void SetRotation(const D3DXVECTOR3& rotation);
	virtual void SetRotation(const D3DXQUATERNION& rotation);
	virtual D3DXVECTOR3 GetEulerAngle() const;
	virtual D3DXQUATERNION GetRotation() const;

	//スケール処理
	virtual void Scale(const D3DXVECTOR3& delta);
	virtual void SetScale(const D3DXVECTOR3& scale);
	virtual D3DXVECTOR3 GetScale() const;

	//向き
	virtual D3DXVECTOR3 Forward() const;
	virtual D3DXVECTOR3 Right() const;
	virtual D3DXVECTOR3 Up() const;

	//ワールド変換設定処理
	virtual void SetWorld(const D3DXMATRIX* parent = NULL) const;
	virtual D3DXMATRIX GetMatrix() const;

	//指定の位置を向かせる処理
	void LookAt(const D3DXVECTOR3& target);
	
protected:
	D3DXVECTOR3 position;	//座標
	D3DXVECTOR3 scale;	//スケール
	D3DXQUATERNION rotation;	//回転
};

#endif