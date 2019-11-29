//=====================================
//
// セレクトビュアー[SelectViewer.cpp]
// 機能：モードセレクト表示用
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "SelectViewer.h"
#include "../../SubScreen/SubScreen.h"
#include "SelectCamera.h"
#include "../../../Framework/Effect/RendererEffect.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "SelectLogo.h"
#include "../../../Framework/Input/input.h"

#include <algorithm>
#include <functional>

//**************************************
// スタティックメンバ初期化
//**************************************
const D3DXVECTOR2 SelectViewer::SubScreenSize = D3DXVECTOR2(960.0f, 320.0f);
const D3DXVECTOR2 SelectViewer::SubScreenPos = D3DXVECTOR2((float)SCREEN_CENTER_X - 480.0f, (float)SCREEN_CENTER_Y);

//=====================================
// コンストラクタ
//=====================================
SelectViewer::SelectViewer() :
	nextMode(0)
{
	// サブスクリーンを作成
	subScreen = new SubScreen(SubScreenSize, SubScreenPos);
	camera = new SelectCamera();

	// リソース読み込み
	ResourceManager::Instance()->MakePolygon("ModeSelect", "data/TEXTURE/Title/ModeSelect.png", D3DXVECTOR2(48.0f, 10.0f), D3DXVECTOR2(1.0f, 3.0f));

	// 各種インスタンスの作成
	logo.reserve(Mode::Max);
	for (int i = 0; i < Mode::Max; i++)
	{
		SelectLogo* p = new SelectLogo();
		p->LoadResource("ModeSelect");
		p->SetTexDiv(D3DXVECTOR2(1.0f, 3.0f));
		p->SetTextureIndex(i);
		p->SetPosition(SelectLogo::InitLogoPos[i]);
		p->SetAngle(SelectLogo::InitAngle[i]);
		logo.push_back(p);
	}
}

//=====================================
// デストラクタ
//=====================================
SelectViewer::~SelectViewer()
{
	SAFE_DELETE(subScreen);
	SAFE_DELETE(camera);
	for (auto& p : logo)
	{
		SAFE_DELETE(p);
	}
	logo.clear();
}

//=====================================
// 更新
//=====================================
void SelectViewer::Update()
{
	camera->Update();

	for (auto& p : logo)
	{
		p->Update();
	}
	// 描画順をソート（奥のものから先に描画するように）
	std::sort(logo.begin(), logo.end(), std::greater<>());

	if (Keyboard::GetPress(DIK_RIGHT))
	{
		if (logo[0]->Moveable())
		{
			nextMode = Math::WrapAround(0, Mode::Max, ++nextMode);
			for (auto& p : logo)
			{
				p->TurnRight();
			}
		}
	}
	if (Keyboard::GetPress(DIK_LEFT))
	{
		if (logo[0]->Moveable())
		{
			nextMode = Math::WrapAround(0, Mode::Max, --nextMode);
			for (auto& p : logo)
			{
				p->TurnLeft();
			}
		}
	}

}

//=====================================
// 描画
//=====================================
void SelectViewer::Draw()
{
	const D3DXCOLOR BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	subScreen->DrawBegin(BackColor);

	const Camera *defaultCamera = Camera::MainCamera();
	Camera::SetMainCamera(camera);
	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	// インスタンスの描画
	for (auto& p : logo)
	{
		p->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	subScreen->DrawTexture();

	subScreen->DrawEnd();

	// カメラ復元
	Camera::SetMainCamera(const_cast<Camera*>(defaultCamera));
	RendererEffect::SetView(defaultCamera->GetViewMtx());
	RendererEffect::SetProjection(defaultCamera->GetProjectionMtx());
}

//=====================================
// シーンチェンジ
//=====================================
int SelectViewer::CheckNextScene()
{
	return nextMode;
}