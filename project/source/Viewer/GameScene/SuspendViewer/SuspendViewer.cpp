//=====================================
//
//SuspendViewer.cpp
//機能:サスペンドビューワー
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SuspendViewer.h"

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Sound/SoundEffect.h"
#include "../../../Sound/SoundConfig.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
SuspendViewer::SuspendViewer() :
	selectedYes(true)
{
	dialogYes = new Polygon2D();
	dialogYes->LoadTexture("data/TEXTURE/Viewer/SuspendViewer/suspendText.png");
	dialogYes->SetUV(0.0f, 0.0f, 1.0f, 0.5f);
	dialogYes->SetPosition({ 750.0f, 590.0f, 0.0f });
	dialogYes->SetSize(150.0f, 75.0f);

	dialogNo = new Polygon2D();
	dialogNo->LoadTexture("data/TEXTURE/Viewer/SuspendViewer/suspendText.png");
	dialogNo->SetUV(0.0f, 0.5f, 1.0f, 0.5f);
	dialogNo->SetPosition({ 1170.0f, 590.0f, 0.0f });
	dialogNo->SetSize(150.0f, 75.0f);

	bg = new Polygon2D();
	bg->LoadTexture("data/TEXTURE/Viewer/SuspendViewer/suspendBG.png");
	bg->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	bg->SetSize(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	bg->SetColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	LoadTexture("data/TEXTURE/Viewer/SuspendViewer/suspendFrame.png");
	transform->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	SetSize(SCREEN_WIDTH / 4.0f, 160.0f);
}

/**************************************
デストラクタ
***************************************/
SuspendViewer::~SuspendViewer()
{
	SAFE_DELETE(dialogYes);
	SAFE_DELETE(dialogNo);
	SAFE_DELETE(bg);
}

/**************************************
更新処理
***************************************/
void SuspendViewer::Update()
{
	if (!active)
		return;

	if (Input::GetTriggerHorizontal())
	{
		selectedYes = !selectedYes;
		SE::Play(SoundConfig::MoveCursor, 0.5f);
	}

	D3DXCOLOR colorYes = selectedYes ? D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) : D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	D3DXCOLOR colorNo = selectedYes ? D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f) : D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	dialogYes->SetColor(colorYes);
	dialogNo->SetColor(colorNo);
}

/**************************************
描画処理
***************************************/
void SuspendViewer::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	bg->Draw();

	Polygon2D::Draw();

	if (selectedYes)
	{
		dialogYes->Draw();
	}
	else
	{
		dialogNo->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

/**************************************
選択結果の取得処理
***************************************/
SuspendViewer::Dialog SuspendViewer::GetSelected() const
{
	return selectedYes ? Yes : No;
}
