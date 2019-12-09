//=============================================================================
//
// 結果ビュアーコントロール処理 [ResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../ResultViewer/ResultScoreViewer.h"
#include "../ParameterContainer/ResultViewerParam.h"
#include "ResultViewer.h"
#include "../GuideViewer/GuideActor.h"
#include "../../../SubScreen/SubScreen.h"
#include "../../../../Framework/Camera/Camera.h"
#include "../../../../Framework/Effect/RendererEffect.h"

#ifdef _DEBUG
#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ResultViewer::ResultViewer()
{
	viewerParam = new ResultViewerParam();
	resultViewer.push_back(scoreViewer = new ResultScoreViewer());

	actor = new GuideActor();
	screen = new SubScreen({ (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }, { 0.0f, 0.0f });
	camera = new Camera();

	//アクターの姿勢を調整
	Transform actorTransform = actor->GetTransform();
	const D3DXVECTOR3 ActorPos = { 13.0f, -14.0f, -10.0f };
	actorTransform.SetPosition(ActorPos);

	actorTransform.LookAt(camera->GetPosition());
	actorTransform.Rotate(180.0f, actorTransform.Up());

	const float ActorAngle = -37.0f;
	actorTransform.Rotate(ActorAngle, actorTransform.Right());

	actor->SetTransform(actorTransform);

	//アニメーションを拍手に変更
	actor->ChangeAnim(GuideActor::AnimState::Clapping, true);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultViewer::~ResultViewer()
{
	SAFE_DELETE(viewerParam);

	//メモリを解放
	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		SAFE_DELETE(resultViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	resultViewer.clear();

	SAFE_DELETE(actor);
	SAFE_DELETE(screen);
	SAFE_DELETE(camera);
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultViewer::Update()
{
	if (!isActive)
		return;

	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Update();
	}

	actor->Update();
	camera->Update();

	//if (Keyboard::GetTrigger(DIK_S))
	//{
	//	scoreViewer->Set();
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダリングターゲットをscreenに切り替えてアクターを描画
	screen->DrawBegin(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	const Camera *defaultCamera = Camera::MainCamera();
	Camera::SetMainCamera(camera);
	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	actor->Draw();

	screen->DrawEnd();

	//カメラ復元
	Camera::SetMainCamera(const_cast<Camera*>(defaultCamera));
	RendererEffect::SetView(defaultCamera->GetViewMtx());
	RendererEffect::SetProjection(defaultCamera->GetProjectionMtx());
	defaultCamera->Set();

	//UI描画
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < resultViewer.size(); i++)
	{
		resultViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// パラメータ受け取る処理
//=============================================================================
void ResultViewer::ReceiveParam(int cityScore, int worldScore, int spaceScore)
{
	int param[ResultViewerParam::fieldTypeMax] = { cityScore ,worldScore ,spaceScore };

	for (int i = 0; i < ResultViewerParam::fieldTypeMax; i++)
	{
		//コンテナに入れて
		viewerParam->score[i] = param[i];

		//コンテナからビュアーに渡す
		scoreViewer->parameterBox[i] = viewerParam->score[i];
	}
}

//=============================================================================
// 描画可否判定のセット
//=============================================================================
void ResultViewer::SetActive(bool flag)
{
	isActive = flag;
}
