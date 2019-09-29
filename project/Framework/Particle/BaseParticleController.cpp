//=====================================
//
//ベースパーティクルコントローラ処理[BaseParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseParticleController.h"
#include "../Tool/DebugWindow.h"
#include "../Resource/ResourceManager.h"
#include "ParticleRenderer.h"
#include "ParticleJsonParser.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
staticメンバ
***************************************/
shared_ptr<ParticleRenderer> BaseParticleController::mRenderer = NULL;

/**************************************
コンストラクタ
***************************************/
BaseParticleController::BaseParticleController() :
	unitBuff(NULL), texture(NULL)
{
	if (!mRenderer)
	{
		mRenderer.reset(new ParticleRenderer());
	}
	renderer = mRenderer;
}

/**************************************
デストラクタ
***************************************/
BaseParticleController::~BaseParticleController()
{
	//テクスチャはResourceManagerにまかせているので開放しない

	SAFE_RELEASE(unitBuff);

	Utility::DeleteContainer(particleContainer);

	Utility::DeleteContainer(emitterContainer);

	renderer.reset();
}

/**************************************
終了処理
***************************************/
void BaseParticleController::Uninit()
{
	for (auto& particle : particleContainer)
	{
		particle->SetActive(false);
	}

	for (auto& emitter : emitterContainer)
	{
		emitter->SetActive(false);
	}
}

/**************************************
更新処理
***************************************/
void BaseParticleController::Update()
{
	//エミッタ更新
	for (BaseEmitter *emitter : emitterContainer)
	{
		emitter->Update();
	}

	//全エミッタに対して放出処理
	for (BaseEmitter* emitter : emitterContainer)
	{
		//放出処理
		bool res = emitter->Emit(particleContainer);

		//放出できるパーティクルが残っていなければbreak
		if (!res)
			break;		
	}

	//パーティクル更新
	for (BaseParticle *particle : particleContainer)
	{
		particle->Update();
	}
}

/**************************************
描画処理
***************************************/
bool BaseParticleController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各パーティクルのパラメータを頂点バッファにセット
	UINT particleCount = 0;
	particleCount = renderer->EmbedUV(particleContainer);

	if (particleCount == 0)
		return false;

	particleCount = renderer->EmbedTransform(particleContainer);

	//ストリームソース設定
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);

	//テクスチャ設定
	pDevice->SetTexture(0, texture);

	//描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	return true;
}

/**************************************
パーティクル単位バッファ作成処理
***************************************/
void BaseParticleController::MakeUnitBuffer(const D3DXVECTOR2& size, const D3DXVECTOR2& texDiv)
{
	if (unitBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &unitBuff, 0);

	ParticleUnit *p;
	unitBuff->Lock(0, 0, (void**)&p, 0);

	//単位サイズ設定
	p[0].vtx = D3DXVECTOR3(-size.x / 2.0f, size.y / 2.0f, 0.0f);
	p[1].vtx = D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, 0.0f);
	p[2].vtx = D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, 0.0f);
	p[3].vtx = D3DXVECTOR3(size.x / 2.0f, -size.y / 2.0f, 0.0f);

	//単位UV設定
	float u = 1.0f / texDiv.x;
	float v = 1.0f / texDiv.y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	unitBuff->Unlock();
}

/**************************************
テクスチャ読み込み処理
***************************************/
void BaseParticleController::LoadTexture(const char* filePath)
{
	ResourceManager::Instance()->GetTexture(filePath, texture);
}

/**************************************
エミッタコンテナ作成処理
***************************************/
void BaseParticleController::MakeEmitterContainer(const ParticleJsonParser & data)
{
	emitterContainer.resize(data.GetEmitterMax());
	for (auto&& emitter : emitterContainer)
	{
		int emitNum = data.GetEmitNum();
		int duration = data.GetDuration();
		emitter = new BaseEmitter(emitNum, duration);
	}
}

/**************************************
エミッタセット処理
***************************************/
BaseEmitter* BaseParticleController::SetEmitter(const D3DXVECTOR3& pos)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->IsActive();
	});

	if (emitter == emitterContainer.end())
		return NULL;

	BaseEmitter* ptr = (*emitter);
	ptr->SetPosition(pos);
	ptr->Init();

	return ptr;

}

/**************************************
エミッタセット処理
***************************************/
BaseEmitter* BaseParticleController::SetEmitter(const Transform& transform)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter *emitter)
	{
		return !emitter->IsActive();
	});

	if (emitter == emitterContainer.end())
		return NULL;

	BaseEmitter* ptr = *emitter;
	ptr->SetTransform(transform);
	ptr->Init();

	return ptr;
}

/**************************************
描画開始処理
***************************************/
void BaseParticleController::BeginDraw()
{
	mRenderer->BeginDraw();
}

/**************************************
描画終了処理
***************************************/
void BaseParticleController::EndDraw()
{
	mRenderer->EndDraw();
}