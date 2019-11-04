/******************************************************************
* @file Game.cpp
* @brief ゲームのコア処理
* @author 立花雄太
******************************************************************/
#include "BaseGame.h"
#include "..\Input\input.h"
#include "..\Camera\Camera.h"
#include "../Light/Light.h"
#include "..\Tool\DebugWindow.h"
#include "..\Tween\Tween.h"
#include "../Tool/ProfilerCPU.h"
#include "../Task/TaskManager.h"
#include "../Transition/TransitionController.h"
#include "../Effect/RendererEffect.h"

Tween* Tween::mInstance = NULL;
/**************************************
コンストラクタ
***************************************/
BaseGame::BaseGame(HINSTANCE hInstance, HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//インスタンス作成
	sceneManager = new SceneManager();
	Tween::mInstance = new Tween();

	//描画領域作成
	MakeScreen();
	MakeRenderTarget();

	//各種初期化
	Input::Init(hInstance, hWnd);
	Light::Init();
	Debug::Init(hWnd, pDevice);
}

/**************************************
デストラクタ
***************************************/
BaseGame::~BaseGame()
{
	sceneManager->Uninit();
	sceneManager->Clear();

	SAFE_RELEASE(renderTexture);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(screenVtx);

	SAFE_DELETE(sceneManager);
	SAFE_DELETE(Tween::mInstance);

	Debug::Uninit();
	Input::Uninit();
}

/**************************************
更新処理
***************************************/
void BaseGame::Update()
{
	Debug::Update();
	Input::Update();

	static bool pause = false;
	if (Keyboard::GetTrigger(DIK_P))
		pause = !pause;

	if (!pause)
	{
		ProfilerCPU::Instance()->Update();

		sceneManager->Update();

		Tween::mInstance->Update();
		TaskManager::Instance()->Update();
		TransitionController::Instance()->Update();
	}
}

/**************************************
描画処理
***************************************/
void BaseGame::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット切り替え
	LPDIRECT3DSURFACE9 oldSuf;
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.05f, 1.0f);
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BackColor, 1.0f, 0);

	//描画用エフェクトへパラメータを設定
	RendererEffect::SetView(Camera::MainCamera()->GetViewMtx());
	RendererEffect::SetProjection(Camera::MainCamera()->GetProjectionMtx());
	RendererEffect::SetLight(0, Light::GetData(0));

	//トランジションマスクを描画
	TransitionController::Instance()->DrawMask();

	//シーンを描画
	sceneManager->Draw();

	//トランジション背景を描画
	TransitionController::Instance()->DrawTransition();

	//レンダーターゲット復元
	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	//バックバッファへ描画
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetStreamSource(0, screenVtx, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//デバッグウィンドウ描画
	ProfilerCPU::Instance()->Draw();
	Debug::Draw();
}

/**************************************
スクリーン作成処理
***************************************/
void BaseGame::MakeScreen()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&screenVtx,
		0);

	VERTEX_2D *pVtx;
	screenVtx->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	screenVtx->Unlock();
}

/**************************************
レンダーターゲット作成処理
***************************************/
void BaseGame::MakeRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーテクスチャ作成
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	renderTexture->GetSurfaceLevel(0, &renderSurface);
}