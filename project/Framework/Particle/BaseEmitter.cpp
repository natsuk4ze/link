//=====================================
//
//ベースエミッタ処理[BaseEmitter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEmitter.h"
#include "BaseParticle.h"
#include "ParticleRenderer.h"

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
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum) :
	GameObject(false),
	emitNum(emitNum),
	duration(2),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum, int duration) :
	GameObject(false),
	emitNum(emitNum),
	duration(duration),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(duration == 0)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNum, int durationMin, int durationMax) :
	GameObject(false),
	emitNum(emitNum),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
コンストラクタ
***************************************/
BaseEmitter::BaseEmitter(int emitNumMin, int emitNumMax, int durationMin, int durationMax) :
	GameObject(false),
	emitNum(Math::RandomRange(emitNumMin, emitNumMax)),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
デストラクタ
***************************************/
BaseEmitter::~BaseEmitter()
{
	Utility::DeleteContainer(particleContainer);
}

/**************************************
初期化処理
***************************************/
void BaseEmitter::Init(const std::function<void(void)>& callback)
{
	cntFrame = 0;
	active = true;
	isFinished = false;
	enableEmit = true;

	this->callback = callback;

	for (auto&& particle : particleContainer)
	{
		particle->SetActive(false);
	}
}

/**************************************
更新処理
***************************************/
void BaseEmitter::Update()
{
	if (!active)
		return;

	cntFrame++;
	Emit();

	//パーティクルの更新
	isFinished = true;
	for (auto&& particle : particleContainer)
	{
		if (!particle->IsActive())
			continue;

		isFinished = false;

		particle->Update();
	}

	//終了確認
	if (cntFrame >= duration && !flgLoop)
	{
		enableEmit = false;

		if (isFinished)
		{
			active = false;

			if(callback != nullptr)
				callback();
		}
	}
}

/**************************************
放出処理
***************************************/
bool BaseEmitter::Emit()
{
	if (!enableEmit)
		return true;

	D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());

	if (useCull)
	{
		if (screenPos.x < 0.0f || screenPos.x > SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y > SCREEN_HEIGHT)
			return true;
	}

	UINT cntEmit = 0;
	for (auto& particle : particleContainer)
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
//bool BaseEmitter::IsActive() const
//{
//	if (!active)
//		return false;
//
//	if (duration == 0)
//		return true;
//
//	return isFinished;
//}

/**************************************
カリング使用設定
***************************************/
void BaseEmitter::UseCulling(bool value)
{
	useCull = value;
}

/**************************************
描画情報をパーティクルレンダラーにわたす
***************************************/
void BaseEmitter::PushRenderParameter(std::shared_ptr<ParticleRenderer> renderer)
{
	if (!active)
		return;

	for (auto&& particle : particleContainer)
	{
		if (!particle->IsActive())
			continue;

		D3DXMATRIX mtxWorld = particle->GetWorldMtx();
		ParticleUV uv = particle->GetUV();

		renderer->PushParticleParameter(mtxWorld, uv);
	}
}

/**************************************
パーティクル放出の停止
***************************************/
void BaseEmitter::Stop()
{
	enableEmit = false;
}

/**************************************
ループ設定
***************************************/
void BaseEmitter::Loop(bool state)
{
	flgLoop = state;
}
