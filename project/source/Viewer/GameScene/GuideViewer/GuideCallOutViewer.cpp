//=============================================================================
//
// ガイド吹き出しビュアー処理 [GuideCallOutViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "GuideCallOutViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GuideCallOutViewer::GuideCallOutViewer()
{
	//テキスト
	text = new TextViewer("data/TEXTURE/Viewer/GuideViewer/GuideCallOutViewer/Text_cinecaption226.ttf", 25);
	text->SetColor(SET_COLOR_BLACK);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 1.5f), (int)(SCREEN_HEIGHT/10*9.1f));

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/GuideViewer/GuideCallOutViewer/CallOut.png");
	bg->size = D3DXVECTOR3(400.0f, 120.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 1.5), (float)(SCREEN_HEIGHT / 10 * 9), 0.0f);
	bg->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GuideCallOutViewer::~GuideCallOutViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void GuideCallOutViewer::Update(void)
{
	//再生処理
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void GuideCallOutViewer::Draw(void)
{
	//再生中なら実行
	if (!isPlaying) return;

	//背景を先に描画
	bg->Draw();

	//テキスト
	text->Draw();
}

//=============================================================================
// 再生処理
//=============================================================================
void GuideCallOutViewer::Play(void)
{
	//再生中なら実行
	if (!isPlaying) return;

	//再生時間
	const int playTime = 3;

	//フレーム更新
	countFrame++;

	//再生時間に達したら再生終了
	if (countFrame >= playTime * 30)
	{
		countFrame = 0;

		isPlaying = false;
	}
}

//=============================================================================
// メッセージセット処理
//=============================================================================
void GuideCallOutViewer::Set(const std::string &message)
{
	//テキストにメッセージをセット
	text->SetText(message);

	//フレームカウントをリセット
	countFrame = 0;

	//再生状態に移行
	isPlaying = true;
}
