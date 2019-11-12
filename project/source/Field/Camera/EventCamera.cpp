//=====================================
//
//EventCamera.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EventCamera.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
コンストラクタ
***************************************/
EventCamera::EventCamera()
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
		transform.SetPosition(position);
	}

	Camera::Update();
}

/**************************************
移動設定処理
***************************************/
void EventCamera::Move(const D3DXVECTOR3 & position, int duration, std::function<void()> callback)
{
	cntMove = 0;
	durationMove = duration;
	startPosition = transform.GetPosition();
	endPosition = position;
	this->callback = callback;
}

/**************************************
元の位置に戻る処理
***************************************/
void EventCamera::Return(int duration, std::function<void()> callback)
{
	cntMove = 0;
	durationMove = duration;
	startPosition = transform.GetPosition();
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
