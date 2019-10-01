//=====================================
//
//トランスフォーム処理[Transform.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Transform.h"

/**************************************
コンストラクタ
***************************************/
Transform::Transform() :
	position(Vector3::Zero),
	rotation(Quaternion::Identity),
	scale(Vector3::One)
{

}

/**************************************
コンストラクタ
***************************************/
Transform::Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale) :
	position(pos),
	rotation(Quaternion::Identity),
	scale(scale)
{
	D3DXQuaternionRotationYawPitchRoll(&this->rotation, rot.y, rot.x, rot.z);
}

/**************************************
コンストラクタ
***************************************/
Transform::Transform(const Transform &src) :
	position(src.position),
	rotation(src.rotation),
	scale(src.scale)
{

}

/**************************************
代入演算子
***************************************/
Transform Transform::operator=(const Transform &src)
{
	this->position = src.position;
	this->rotation = src.rotation;
	this->scale = src.scale;

	return *this;
}

/**************************************
移動処理
***************************************/
void Transform::Move(const D3DXVECTOR3 & velocity)
{
	position += velocity;
}

/**************************************
移動処理
***************************************/
void Transform::SetPosition(const D3DXVECTOR3 & position)
{
	this->position = position;
}

/**************************************
移動処理
***************************************/
D3DXVECTOR3 Transform::GetPosition() const
{
	return position;
}

/**************************************
回転処理
***************************************/
void Transform::Rotate(float degX, float degY, float degZ)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(degY), D3DXToRadian(degX), D3DXToRadian(degZ));
	D3DXQuaternionMultiply(&rotation, &rotation, &q);
}

/***************************************
回転処理
***************************************/
void Transform::Rotate(float deg, const D3DXVECTOR3& axis)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationAxis(&q, &axis, D3DXToRadian(deg));
	D3DXQuaternionMultiply(&rotation, &rotation, &q);
}

/**************************************
移動処理
***************************************/
void Transform::SetRotation(const D3DXVECTOR3 & rotation)
{
	this->rotation = Quaternion::ToQuaternion(rotation);
}

/**************************************
移動処理
***************************************/
void Transform::SetRotation(const D3DXQUATERNION & rotation)
{
	this->rotation = rotation;
}

/***************************************
オイラー角取得処理
***************************************/
D3DXVECTOR3 Transform::GetEulerAngle() const
{
	return Quaternion::ToEuler(rotation);
}

/**************************************
移動処理
***************************************/
D3DXQUATERNION Transform::GetRotation() const
{
	return rotation;
}

/**************************************
移動処理
***************************************/
void Transform::Scale(const D3DXVECTOR3& delta)
{
	scale.x *= delta.x;
	scale.y *= delta.y;
	scale.z *= delta.z;
}

/**************************************
移動処理
***************************************/
void Transform::SetScale(const D3DXVECTOR3 & scale)
{
	this->scale = scale;
}

/**************************************
移動処理
***************************************/
D3DXVECTOR3 Transform::GetScale() const
{
	return scale;
}

/**************************************
ワールド変換処理
***************************************/
void Transform::SetWorld(const D3DXMATRIX* parent) const
{
	D3DXMATRIX world = GetMatrix();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//親を反映
	if (parent != NULL)
	{
		D3DXMatrixMultiply(&world, &world, parent);
	}

	pDevice->SetTransform(D3DTS_WORLD, &world);
}

/**************************************
前方計算処理
***************************************/
D3DXVECTOR3 Transform::Forward() const
{
	D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &this->rotation);
	D3DXVec3TransformCoord(&forward, &forward, &rotation);

	return forward;
}

/**************************************
右方計算処理
***************************************/
D3DXVECTOR3 Transform::Right() const
{
	D3DXVECTOR3 right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &this->rotation);
	D3DXVec3TransformCoord(&right, &right, &rotation);

	return right;
}

/**************************************
上方計算処理
***************************************/
D3DXVECTOR3 Transform::Up() const
{
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &this->rotation);
	D3DXVec3TransformCoord(&up, &up, &rotation);

	return up;
}

/**************************************
ワールド行列取得処理
***************************************/
D3DXMATRIX Transform::GetMatrix() const
{
	/*************************************
	NOTE:正直に行列計算するより、要素を直接計算した方が早かったので
	回転だけ行列で、それ以外は直接計算している
	*************************************/
	D3DXMATRIX world;

	//回転
	D3DXMatrixRotationQuaternion(&world, &this->rotation);

	//スケール
	world._11 *= scale.x;
	world._12 *= scale.x;
	world._13 *= scale.x;

	world._21 *= scale.y;
	world._22 *= scale.y;
	world._23 *= scale.y;

	world._31 *= scale.z;
	world._32 *= scale.z;
	world._33 *= scale.z;

	//移動
	world._41 = position.x;
	world._42 = position.y;
	world._43 = position.z;

	return world;
}