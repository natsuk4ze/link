//=====================================
//
// ガイドビュアー[GuideViewer.cpp]
// 機能：ガイド役キャラクター表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideViewer.h"
#include "GuideCallOutViewer.h"
#include "../../../../Framework/Resource/ResourceManager.h"
#include "../../../../Framework/Effect/RendererEffect.h"
#include "GuideCamera.h"
#include "GuideViewerBG.h"
#include "../../../SubScreen/SubScreen.h"

#ifdef _DEBUG

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"

#endif

//**************************************
// スタティックメンバ初期化
//**************************************
const D3DXVECTOR2 GuideViewer::SubScreenSize = D3DXVECTOR2(360.0f, 360.0f);
const D3DXVECTOR2 GuideViewer::SubScreenPosition = D3DXVECTOR2(30.0f, 690.0f);

//=====================================
// コンストラクタ
//=====================================
GuideViewer::GuideViewer()
{
	// 描画用サブスクリーンの作成
	subScreen = new SubScreen(SubScreenSize, SubScreenPosition);
	camera = new GuideCamera();

	// リソース読み込み
	ResourceManager::Instance()->MakePolygon("GuideViewerBG", "data/TEXTURE/VIewer/GameViewer/GuideViewer/Circuit.jpg", D3DXVECTOR2(100.0f, 100.0f));

	// 各種インスタンスの作成
	actor = new GuideActor();
	bg = new GuideViewerBG();
	filter = new CRTFilter((DWORD)SubScreenSize.x, (DWORD)SubScreenSize.y);
	callOutViewer = new GuideCallOutViewer();
}

//=====================================
// デストラクタ
//=====================================
GuideViewer::~GuideViewer()
{
	SAFE_DELETE(subScreen);

	SAFE_DELETE(actor);
	SAFE_DELETE(camera);
	SAFE_DELETE(bg);
	SAFE_DELETE(filter);

	SAFE_DELETE(callOutViewer);
}

//=====================================
// 更新
//=====================================
void GuideViewer::Update()
{

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_G))
	{
		SetGuideViewer("テストを再生中です～\n頑張って下さい～");
	}

#endif

	camera->Update();
	actor->Update();
	bg->Update();
	filter->SetTime();
	filter->SetScreenParam(SubScreenSize.x, SubScreenSize.y);
	callOutViewer->Update();
}

//=====================================
// 描画
//=====================================
void GuideViewer::Draw()
{
	if (!isActive)
		return;

	const D3DXCOLOR BackColor = D3DXCOLOR(0.6f, 0.6f, 1.0f, 0.8f);
	subScreen->DrawBegin(BackColor);

	const Camera *defaultCamera = Camera::MainCamera();
	Camera::SetMainCamera(camera);
	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	// インスタンスの描画
	bg->Draw();
	actor->Draw();

	for (int i = 0; i < 4; i++)
	{
		subScreen->DrawTexture();
		filter->Draw(i);
	}

	subScreen->DrawEnd();

	//カメラを復元
	Camera::SetMainCamera(const_cast<Camera*>(defaultCamera));
	RendererEffect::SetView(defaultCamera->GetViewMtx());
	RendererEffect::SetProjection(defaultCamera->GetProjectionMtx());

	//////////////以下、ビュアー処理/////////////////////
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	callOutViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=====================================
// アクターのアニメーション切り替え
//=====================================
void GuideViewer::ChangeAnim(GuideActor::AnimState next)
{
	actor->ChangeAnim(next);
}

//=====================================
// 描画可否判定のセット
//=====================================
void GuideViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=====================================
// ガイドビュアーセット処理
//=====================================
void GuideViewer::SetGuideViewer(const std::string &message)
{
	// イベントメッセージがあったら実行
	if (message.empty()) return;

	ChangeAnim(GuideActor::AnimState::TalkingTypeB);

	callOutViewer->Set(message);
}