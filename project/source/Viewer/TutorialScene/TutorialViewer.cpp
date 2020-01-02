//=============================================================================
//
// チュートリアルビューアクラス [TutorialViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "TutorialViewer.h"
#include "../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"

#include "../../../Framework/Core/Utility.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Input/input.h"

/**************************************
staticメンバ
***************************************/
const D3DXVECTOR3 DefaultTexturePos = D3DXVECTOR3(SCREEN_CENTER_X, 410.0f, 0.0f);
const char* TexturePath[TutorialViewer::HelpTextureType::Max] =
{
	"data/TEXTURE/Viewer/TutorialViewer/LinkRoad.png",
	"data/TEXTURE/Viewer/TutorialViewer/Develop.png",
	"data/TEXTURE/Viewer/TutorialViewer/ChangeCamera.png",
	"data/TEXTURE/Viewer/TutorialViewer/Event.png",
	"data/TEXTURE/Viewer/TutorialViewer/HighScore.png",
};


//=============================================================================
// コンストラクタ
//=============================================================================
TutorialViewer::TutorialViewer() :
	TextureNum(LinkRoad)
{
	// 非表示する
	isPlaying = false;

	BackGround = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	BackGround->LoadTexture("data/TEXTURE/Viewer/TutorialViewer/BackGround.png");
	BackGround->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	BackGround->SetAlpha(0.5f);

	HelpTexture.reserve(HelpTextureType::Max);
	for (int i = 0; i < HelpTextureType::Max; i++)
	{
		HelpTexture.push_back(new TextureDrawer({ 1280.0f, 820.0f }));
		HelpTexture.at(i)->LoadTexture(TexturePath[i]);
		HelpTexture.at(i)->SetPosition(DefaultTexturePos);
	}

	MessageFrame = new TextureDrawer(D3DXVECTOR2(1280.0f, 250.0f));
	MessageFrame->LoadTexture("data/TEXTURE/Viewer/TutorialViewer/MessageFrame.png");
	MessageFrame->SetPosition({ SCREEN_CENTER_X, 950.0f, 0.0f });

	DescriptionText = new TextViewer("マキナス 4 Square", 50);;
	DescriptionText->SetPosition(D3DXVECTOR3(350.0f, 900.0f, 0.0f));
	DescriptionText->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);
	DescriptionText->SetText("ここは操作説明です。");
}

//=============================================================================
// デストラクタ
//=============================================================================
TutorialViewer::~TutorialViewer()
{
	SAFE_DELETE(BackGround);
	SAFE_DELETE(MessageFrame);
	SAFE_DELETE(DescriptionText);
	Utility::DeleteContainer(HelpTexture);
}

//=============================================================================
// 更新処理
//=============================================================================
void TutorialViewer::Update()
{
	if (!isPlaying)
		return;

	HelpTexture.at(TextureNum)->Update();

	/*
	static D3DXVECTOR3 FramePos = D3DXVECTOR3(SCREEN_CENTER_X, 925.0f, 0.0f);
	static D3DXVECTOR3 TextPos = D3DXVECTOR3(350.0f, 900.0f, 0.0f);
	Debug::Begin("TutorialLayout");
	Debug::Input("FramePos", FramePos);
	Debug::Input("TextPos", TextPos);
	MessageFrame->SetPosition(FramePos);
	DescriptionText->SetPosition(TextPos);
	Debug::End();
	*/
}

//=============================================================================
// 描画処理
//=============================================================================
void TutorialViewer::Draw()
{
	if (!isPlaying)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	BackGround->Draw();

	HelpTexture.at(TextureNum)->Draw();

	MessageFrame->Draw();
	DescriptionText->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// チュートリアルを表示する
//=============================================================================
void TutorialViewer::ShowTutorial(HelpTextureType Type)
{
	GuideViewer::Instance()->SetActive(false);
	isPlaying = true;
	TextureNum = Type;

	HelpTexture.at(TextureNum)->SetAlpha(0.0f);
	HelpTexture.at(TextureNum)->Fade(15.0f, 1.0f);
}
