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
	TextureNum(LinkRoad),
	IsShowTexture(false)
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
	DescriptionText->SetPosition(D3DXVECTOR3(350.0f, 950.0f, 0.0f));
	DescriptionText->SetHorizontalAlignment(TextViewer::HorizontalAlignment::Left);
	DescriptionText->SetText("ここは操作説明です。");

	ExitText = new TextViewer("マキナス 4 Square", 80);;
	ExitText->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 950.0f, 0.0f));
	ExitText->SetText("");
	ExitText->SetActive(false);
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
// 初期化
//=============================================================================
void TutorialViewer::Init(void)
{
	isPlaying = false;
	IsShowTexture = false;
	TextureNum = LinkRoad;
	BackGround->SetVisible(false);
	HelpTexture.at(TextureNum)->SetVisible(false);
	MessageFrame->SetVisible(false);
	DescriptionText->SetActive(false);
	ExitText->SetActive(false);
	ExitText->SetText("");
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

	// 黒い背景
	BackGround->Draw();

	// 説明画面
	HelpTexture.at(TextureNum)->Draw();

	// テキストのフレーム
	MessageFrame->Draw();

	// 説明テキスト
	DescriptionText->Draw();

	// 終了テキスト
	ExitText->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// チュートリアルの説明画面を表示
//=============================================================================
void TutorialViewer::ShowTutorial(HelpTextureType Type)
{
	// ガイド役の画面を非表示
	GuideViewer::Instance()->SetActive(false);

	// 初期化
	isPlaying = true;
	IsShowTexture = true;
	TextureNum = Type;
	BackGround->SetVisible(true);
	HelpTexture.at(TextureNum)->SetVisible(true);
	MessageFrame->SetVisible(true);
	DescriptionText->SetActive(true);
	ExitText->SetActive(false);

	// 画像のフェイドイン
	HelpTexture.at(TextureNum)->SetAlpha(0.0f);
	HelpTexture.at(TextureNum)->Fade(15.0f, 1.0f);

	// 説明テキストの設置
	std::string text = "";
	switch (Type)
	{
	case TutorialViewer::LinkRoad:
		text += "町同士を繋げるようにルートを作ると、人が行き来して発展します。\n";
		text += "道の長さに制限はありませんが、\n";
		text += "道を作るときは町同士が繋がっている必要があります。";
		DescriptionText->SetText(text);
		ExitText->SetText("町を道で繋ぐ");
		break;

	case TutorialViewer::Develop:
		text += "川や山などを指定してルートを作ると、\n";
		text += "開拓して道を置けるようになります。\n";
		text += "開拓1マスにつき、画面左のストックを1個使います。\n";
		DescriptionText->SetText(text);
		ExitText->SetText("フィールドを開拓する");
		break;

	case TutorialViewer::ChangeCamera:
		text += "カメラを動かして視点を切り替えることができます。\n";
		text += "フィールドを遠くから眺めて開発計画を立てましょう。\n";
		text += "遠くから眺めてる間はルートを作ることができません。";
		DescriptionText->SetText(text);
		ExitText->SetText("カメラを切り替える");
		break;

	case TutorialViewer::EventHappend:
		text += "光が出ているマスに道を置くと様々なイベントが発生します。\n";
		text += "プレイヤーにとって良いイベントだけでなく、\n";
		text += "悪いイベントが起きることもあるので注意しましょう。";
		DescriptionText->SetText(text);
		ExitText->SetText("道でイベントマスを覆う");
		break;

	case TutorialViewer::HighScore:
		text += "一度にたくさんの町を繋げられるように道を繋ぐと、\n";
		text += "たくさんのポイントが入り、スコアが高くなります。\n";
		text += "ハイスコアを目指して頑張りましょう。\n";
		DescriptionText->SetText(text);
		if (GamePad::GetPadCount() == 0)
		{
			ExitText->SetText("チュートリアル終了：Enter Key");
		}
		else
		{
			ExitText->SetText("チュートリアル終了：Option Button");
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// ヘルプテキストを表示
//=============================================================================
void TutorialViewer::SetHelpMessage(void)
{
	isPlaying = true;
	BackGround->SetVisible(false);
	HelpTexture.at(TextureNum)->SetVisible(false);
	MessageFrame->SetVisible(false);
	DescriptionText->SetActive(false);
	ExitText->SetActive(true);
}
