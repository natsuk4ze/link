//=====================================
//
//EventCamera.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EventCamera.h"
#include "FieldCamera.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
コンストラクタ
***************************************/
EventCamera::EventCamera() :
	referencePosition(Vector3::Zero),
	cntMove(0),
	durationMove(0),
	flgLookAt(false),
	targetObject(nullptr)
{
}

/**************************************
デストラクタ
***************************************/
EventCamera::~EventCamera()
{
}

/**************************************
初期化処理
***************************************/
void EventCamera::Init()
{
	//現在のメインカメラのパラメータをコピー
	*this = *Camera::mainCamera;

	//元のカメラをキャッシュ
	defaultMainCamera = Camera::mainCamera;

	//自身をメインカメラにセット
	Camera::SetMainCamera(this);

	//パラメータ初期化
	int cntMove = durationMove = 0;
}

/**************************************
復元処理
***************************************/
void EventCamera::Restore()
{
	//元のメインカメラに戻す
	Camera::SetMainCamera(defaultMainCamera);

	//ターゲットを解除
	targetObject = nullptr;
}

/**************************************
更新処理
***************************************/
void EventCamera::Update()
{
	//移動処理
	if (cntMove < durationMove)
	{
		cntMove++;
		float t = (float)cntMove / durationMove;
		D3DXVECTOR3 position = Easing::EaseValue(t, startPosition, endPosition, EaseType::OutCubic);
		transform->SetPosition(position);

		if (cntMove == durationMove && callback != nullptr)
			callback();
	}

	if (targetObject != nullptr)
	{
		transform->LookAt(targetObject->GetPosition());
	}

	Camera::Update();
}

/**************************************
移動設定処理
***************************************/
void EventCamera::Move(const D3DXVECTOR3 & position, int duration, float eyeDistance, std::function<void()> callback)
{
	flgLookAt = true;
	cntMove = 0;
	durationMove = duration;
	startPosition = transform->GetPosition();
	endPosition = position;
	this->callback = callback;

	referencePosition = transform->Forward() * eyeDistance + transform->GetPosition();
}

/**************************************
平行移動処理
***************************************/
void EventCamera::Translation(const D3DXVECTOR3 & position, int duration, std::function<void()> callback)
{
	float angleY = D3DXToRadian(FieldCamera::CameraAngleY);
	float angleXZ = D3DXToRadian(FieldCamera::InitCameraAngle);

	D3DXVECTOR3 offset = D3DXVECTOR3(
		cosf(angleY) * cosf(angleXZ),
		sinf(angleY),
		cosf(angleY) * sinf(angleXZ)) * FieldCamera::LengthFromTarget;

	flgLookAt = false;
	cntMove = 0;
	durationMove = duration;
	startPosition = transform->GetPosition();
	endPosition = position + offset;
	this->callback = callback;
}

/**************************************
元の位置に戻る処理
***************************************/
void EventCamera::Return(int duration, std::function<void()> callback)
{
	flgLookAt = false;
	cntMove = 0;
	durationMove = duration;
	startPosition = transform->GetPosition();
	endPosition = defaultMainCamera->GetTransform().GetPosition();
	this->callback = callback;
}

/**************************************
代入演算子
***************************************/
EventCamera & EventCamera::operator=(const Camera & rhs)
{
	Camera* downThis = dynamic_cast<Camera*>(this);
	*downThis = rhs;
	return *this;
}

/**************************************
ターゲット指定
***************************************/
void EventCamera::SetTargetObject(GameObject * target)
{
	targetObject = target;
}
