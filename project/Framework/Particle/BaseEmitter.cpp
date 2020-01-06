//=====================================
//
//ベースエミッタ処理[BaseEmitter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEmitter.h"
#include "BaseParticle.h"
#include "../Camera/Camera.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter() :
	GameObject(false),
	emitNum(1),
	duration(1),
	useCull(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum) :
	GameObject(false),
	emitNum(emitNum),
	duration(2),
	useCull(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum, int duration) :
	GameObject(false),
	emitNum(emitNum),
	duration(duration),
	useCull(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum, int durationMin, int durationMax) :
	GameObject(false),
	emitNum(emitNum),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNumMin, int emitNumMax, int durationMin, int durationMax) :
	GameObject(false),
	emitNum(Math::RandomRange(emitNumMin, emitNumMax)),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false)
{

}

/**************************************
デストラクタ
***************************************/
BaseEmitter::~BaseEmitter()
{

}

/**************************************
初期化処理
***************************************/
void BaseEmitter::Init(std::function<void(void)>& callback)
{
	cntFrame = 0;
	active = true;
	this->callback = callback;
}

/**************************************
更新処理
***************************************/
void BaseEmitter::Update()
{
	if (!IsActive())
		return;

	cntFrame++;

	if (cntFrame == duration && callback != nullptr)
	{
		callback();
	}
}

/**************************************
放出処理
***************************************/
bool BaseEmitter::Emit(std::vector<BaseParticle*>& container)
{
	if (!IsActive())
		return true;

	D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());

	if (useCull)
	{
		if (screenPos.x < 0.0f || screenPos.x > SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y > SCREEN_HEIGHT)
			return true;
	}

	UINT cntEmit = 0;
	for (auto& particle : container)
	{
		if (particle->IsActive())
			continue;

		//初期化処理
		particle->SetTransform(*transform);
		particle->Init();

		//カウント
		cntEmit++;

		//決められ数だけ放出していたら終了
		if (cntEmit == emitNum)
			return true;
	}

	return false;
}

/**************************************
アクティブ判定
***************************************/
bool BaseEmitter::IsActive() const
{
	if (!active)
		return false;

	if (duration == 0)
		return true;

	return cntFrame <= duration;
}

/**************************************
カリング使用設定
***************************************/
void BaseEmitter::UseCulling(bool value)
{
	useCull = value;
}