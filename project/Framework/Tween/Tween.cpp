//=====================================
//
//トゥイーン処理[Tween.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Tween.h"
#include "../Math/Quaternion.h"
#include <algorithm>

using namespace std;
/**************************************
マクロ定義
***************************************/
bool Tween::PauseFlag = false;

/**************************************
コンストラクタ
***************************************/
Tween::Tween()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

/**************************************
デストラクタ
***************************************/
Tween::~Tween()
{
	for (auto&& tweener : tweenerContainer)
	{
		SAFE_DELETE(tweener);
	}
	tweenerContainer.clear();

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

/**************************************
更新処理
***************************************/
void Tween::Update()
{
	// ゲーム停止中
	if (PauseFlag)
		return;

	for (auto&& tweener : tweenerContainer)
	{
		tweener->Update();
	}

	ClearContainer();
}

/**************************************
コンテナクリア処理
***************************************/
void Tween::ClearContainer()
{
	for (auto&& tweener : tweenerContainer)
	{
		if (!tweener->IsFinished())
			continue;

		SAFE_DELETE(tweener);
	}

	tweenerContainer.remove_if([](auto&& tweener)
	{
		return tweener == NULL;
	});
}

/**************************************
クリア処理
***************************************/
void Tween::ClearAll()
{
	for (auto&& tweener : tweenerContainer)
	{
		SAFE_DELETE(tweener);
	}

	tweenerContainer.clear();
}

/**************************************
移動処理
***************************************/
void Tween::Move(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback)
{
	MoveTweener *tweener = new MoveTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
移動処理
***************************************/
void Tween::Move(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetPosition();
	Move(ref, start, end, duration, type, callback);
}

/**************************************
スケール処理
***************************************/
void Tween::Scale(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback)
{
	ScaleTweener *tweener = new ScaleTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
スケール処理
***************************************/
void Tween::Scale(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetScale();
	Scale(ref, start, end, duration, type, callback);
}

/**************************************
回転処理
***************************************/
void Tween::Rotate(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback)
{
	RotateTweener *tweener = new RotateTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
回転処理
***************************************/
void Tween::Rotate(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetEulerAngle();
	Rotate(ref, start, end, duration, type, callback);
}

/**************************************
方向処理
***************************************/
void Tween::Turn(GameObject & ref, const D3DXVECTOR3 & end, int duration, EaseType type, const D3DXVECTOR3& dummyAxis, std::function<void()> callback)
{
	//始点となるクォータニオンを求める
	D3DXQUATERNION start = ref.transform->GetRotation();

	//終点となるクォータニオンを求める
	D3DXVECTOR3 axis = Vector3::Axis(ref.transform->Forward(), end);
	float angle = Vector3::Angle(ref.transform->Forward(), end);

	//axisがゼロベクトル（始点の向きと終点の向きが並行）の場合はダミーアクシスを使用
	if (Vector3::Equal(axis, Vector3::Zero))
	{
		axis = dummyAxis;
	}

	D3DXQUATERNION rotQ;
	D3DXQuaternionRotationAxis(&rotQ, &axis, D3DXToRadian(angle));

	D3DXQUATERNION endQuaternion = start * rotQ;

	//回転Tweener作成
	RotateTweener *tweener = new RotateTweener(ref.transform, start, endQuaternion, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
Tweenerコンストラクタ
***************************************/
Tween::Tweener::Tweener(std::shared_ptr<Transform>& ref, int duration, EaseType type, Callback callback) :
	reference(ref),
	cntFrame(0),
	duration(duration),
	type(type),
	callback(callback)
{

}

/**************************************
Tweenerデストラクタ
***************************************/
Tween::Tweener::~Tweener()
{
	reference.reset();
}

/**************************************
Tweener終了判定
***************************************/
inline bool Tween::Tweener::IsFinished()
{
	if (reference.expired())
		return true;

	return cntFrame >= duration;
}

/**************************************
コールバックのチェック判定
***************************************/
inline void Tween::Tweener::CheckCallback()
{
	if (cntFrame < duration)
		return;

	if (callback == nullptr)
		return;

	callback();
}

/**************************************
MoveTweenerコンストラクタ
***************************************/
Tween::MoveTweener::MoveTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback) :
	Tweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
MoveTweener更新処理
***************************************/
void Tween::MoveTweener::Update()
{
	cntFrame++;

	shared_ptr<Transform> transform = reference.lock();
	if (transform)
	{
		float t = (float)cntFrame / duration;
		transform->SetPosition(Easing::EaseValue(t, start, end, type));
		CheckCallback();
	}
}

/**************************************
ScaleTweenerコンストラクタ
***************************************/
Tween::ScaleTweener::ScaleTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback) :
	Tweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
ScaleTweener更新処理
***************************************/
void Tween::ScaleTweener::Update()
{
	cntFrame++;

	shared_ptr<Transform> transform = reference.lock();
	if (transform)
	{
		float t = (float)cntFrame / duration;
		transform->SetScale(Easing::EaseValue(t, start, end, type));
		CheckCallback();
	}
}

/**************************************
RotateTweenerコンストラクタ
***************************************/
Tween::RotateTweener::RotateTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback) :
	Tweener(ref, duration, type, callback),
	start(Quaternion::ToQuaternion(start)),
	end(Quaternion::ToQuaternion(end))
{

}

/**************************************
RotateTweenerコンストラクタ
***************************************/
Tween::RotateTweener::RotateTweener(std::shared_ptr<Transform>& ref, const D3DXQUATERNION & start, const D3DXQUATERNION & end, int duration, EaseType type, Callback callback) :
	Tweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
RotateTweener更新処理
***************************************/
void Tween::RotateTweener::Update()
{
	cntFrame++;

	shared_ptr<Transform> transform = reference.lock();
	if (transform)
	{
		float t = Easing::EaseValue((float)cntFrame / duration, 0.0f, 1.0f, type);
		D3DXQUATERNION quaternion;
		D3DXQuaternionSlerp(&quaternion, &start, &end, t);
		transform->SetRotation(quaternion);
		CheckCallback();
	}
}