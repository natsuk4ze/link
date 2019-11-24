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

//**************************************
// スタティックメンバ初期化
//**************************************
const D3DXVECTOR2 SelectViewer::SubScreenSize = D3DXVECTOR2(960.0f, 640.0f);
const D3DXVECTOR2 SelectViewer::SubScreenPos = D3DXVECTOR2((float)SCREEN_CENTER_X - 480.0f, (float)SCREEN_CENTER_Y);

//=====================================
// コンストラクタ
//=====================================
SelectViewer::SelectViewer()
{
	// サブスクリーンを作成
	subScreen = new SubScreen(SubScreenSize, SubScreenPos);
	camera = new SelectCamera();

	// リソース読み込み
	ResourceManager::Instance()->MakePolygon("ModeSelect", "data/TEXTURE/Title/ModeSelect.png", D3DXVECTOR2(50.0f, 16.7f), D3DXVECTOR2(1.0f, 3.0f));

	// 各種インスタンスの作成
	logo[GameStart] = new SelectLogo();
	logo[GameStart]->LoadResource("ModeSelect");
	logo[GameStart]->SetTextureIndex(0);
	logo[GameStart]->SetPosition(Vector3::Zero);
	logo[TrophyCheck] = new SelectLogo();
	logo[TrophyCheck]->LoadResource("ModeSelect");
	logo[TrophyCheck]->SetPosition(Vector3::Zero);
	logo[TrophyCheck]->SetTextureIndex(1);
	logo[Exit] = new SelectLogo();
	logo[Exit]->LoadResource("ModeSelect");
	logo[Exit]->SetPosition(Vector3::Zero);
	logo[Exit]->SetTextureIndex(2);
}

//=====================================
// デストラクタ
//=====================================
SelectViewer::~SelectViewer()
{
	SAFE_DELETE(subScreen);
	SAFE_DELETE(camera);
	for (int i = 0; i < Mode::Max; i++)
	{
		SAFE_DELETE(logo[Mode(i)]);
	}
}

//=====================================
// コンストラクタ
//=====================================
void SelectViewer::Update()
{
	camera->Update();

	for (int i = 0; i < Mode::Max; i++)
	{
		logo[Mode(i)]->Update();
	}
}

void SelectViewer::Draw()
{
	const D3DXCOLOR BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	subScreen->DrawBegin(BackColor);

	const Camera *defaultCamera = Camera::MainCamera();
	Camera::SetMainCamera(camera);
	camera->Set();

	RendererEffect::SetView(camera->GetViewMtx());
	RendererEffect::SetProjection(camera->GetProjectionMtx());

	// インスタンスの描画
	for (int i = 0; i < Mode::Max; i++)
	{
		logo[Mode(0)]->Draw();
	}

	subScreen->DrawTexture();

	subScreen->DrawEnd();

	// カメラ復元
	Camera::SetMainCamera(const_cast<Camera*>(defaultCamera));
	RendererEffect::SetView(defaultCamera->GetViewMtx());
	RendererEffect::SetProjection(defaultCamera->GetProjectionMtx());
}
