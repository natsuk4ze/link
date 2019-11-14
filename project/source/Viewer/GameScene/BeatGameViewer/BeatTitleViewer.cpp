//=============================================================================
//
// 連打ゲームタイトルビュアー処理 [BeatTitleViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatTitleViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BeatTitleViewer::BeatTitleViewer()
{
	//テキスト
	title = new BaseViewerDrawer();
	title->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatTitleViewer/Title.png");
	title->size = D3DXVECTOR3(1325.0f, 250.0f, 0.0f);
	title->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	title->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT /12, 0.0f);
	title->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatTitleViewer::~BeatTitleViewer()
{
	SAFE_DELETE(title);
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatTitleViewer::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void BeatTitleViewer::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	//タイトル
	title->Draw();
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void BeatTitleViewer::PassTexture(TitleID id)
{
	//テキストのUVを変更
	title->SetTexture(1, Max, id);
}

//=============================================================================
// テロップセット処理
//=============================================================================
void BeatTitleViewer::Set(TitleID id)
{
	//テクスチャ情報受け渡し
	PassTexture(id);

	//再生状態にする
	isPlaying = true;
}
