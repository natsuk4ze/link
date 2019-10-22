//=====================================
//
//シーンパーティクルマネージャ処理[SceneParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SceneParticleManager.h"
#include "../PostEffect/CrossFilterController.h"
#include "../PostEffect/ScreenObject.h"
#include "BaseParticleController.h"
#include "../PostEffect/CrossFilterController.h"
#include "../Tool/DebugWindow.h"

/**************************************
マクロ定義
***************************************/
#define SCENEMPARTICLEMANAGER_LABEL		"ParticleManager"

/**************************************
コンストラクタ
***************************************/
SceneParticleManager::SceneParticleManager() :
	renderTexture(NULL),
	renderSurface(NULL),
	screenObj(NULL),
	oldSuf(NULL),
	initialized(false)
{
}

/**************************************
初期化処理
***************************************/
void SceneParticleManager::Init()
{
	//シングルトン化のため、ここでリソースを作成
	if (!initialized)
	{
		CreateRenderTarget();
		initialized = true;
		crossFilter = new CrossFilterController();
	}
}

/**************************************
終了処理
***************************************/
void SceneParticleManager::Uninit()
{
	for (auto& controller : controllers)
	{
		controller->Uninit();
	}

	//シングルトンのためここでリソース解放
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
	SAFE_DELETE(crossFilter);

	Utility::DeleteContainer(controllers);

	initialized = false;
}

/**************************************
更新処理
***************************************/
void SceneParticleManager::Update()
{
	for (auto& controller : controllers)
	{
		controller->Update();
	}
}

/**************************************
描画処理
***************************************/
void SceneParticleManager::Draw()
{
	//レンダーパラメータ切り替え
	ChangeRenderParameter();

	//インスタンシング描画開始
	BaseParticleController::BeginDraw();

	//描画
	bool isDrewd = false;
	for (auto& controller : controllers)
	{
		isDrewd |= controller->Draw();
	}

	//インスタンシング描画終了
	BaseParticleController::EndDraw();

	//すべての結果を元のレンダーターゲットに描画
	RestoreRenderParameter();
	screenObj->Draw();

	//リリース版のみクロスフィルタを適用する
#ifndef _DEBUG	
	//if (isDrewd)
		crossFilter->Draw(renderTexture);
#endif

	//レンダーステート復元
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	Debug::Begin("Particle");
	Debug::DrawTexture(renderTexture, { 200.0f, 100.0f });
	Debug::End();
}

/**************************************
発生処理
***************************************/
BaseEmitter* SceneParticleManager::Generate(UINT id, const D3DXVECTOR3& pos)
{
	assert(id >= 0 && id < controllers.size());

	return controllers[id]->SetEmitter(pos);
}

/**************************************
発生処理
***************************************/
BaseEmitter* SceneParticleManager::Generate(UINT id, const Transform& transform)
{
	assert(id >= 0 && id < controllers.size());

	return controllers[id]->SetEmitter(transform);
}

/**************************************
レンダーターゲット作成処理
***************************************/
void SceneParticleManager::CreateRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット作成
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	//サーフェイス取得
	renderTexture->GetSurfaceLevel(0, &renderSurface);

	//ビューポート作成
	pDevice->GetViewport(&viewPort);
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;

	//描画用スクリーンオブジェクト作成
	screenObj = new ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************
レンダーパラメータ変更処理
***************************************/
void SceneParticleManager::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲットとビューポートをキャッシュ
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->GetViewport(&oldViewport);

	//レンダーターゲット切り替え
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);

	//レンダーステート切り替え
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
}

/**************************************
レンダーパラメータ復元処理
***************************************/
void SceneParticleManager::RestoreRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}