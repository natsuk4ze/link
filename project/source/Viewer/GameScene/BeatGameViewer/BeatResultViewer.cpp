//=============================================================================
//
// 連打ゲーム結果ビュアー処理 [BeatResultViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "BeatResultViewer.h"

#include "../../../../main.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BeatResultViewer::BeatResultViewer()
{
	//テキスト
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatResultViewer/Text.png");
	text->size = D3DXVECTOR3(512.0f, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(-SCREEN_WIDTH * 1.5, SCREEN_CENTER_Y, 0.0f);
	text->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatResultViewer/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	bg->MakeVertex();

	//アニメーション
	anim = new ViewerAnimater();
	std::vector<std::function<void()>> vec = {
		[=] {
		//背景オープン
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, 128.0f), 15.0f, OutCirc);
	},
		[=] {
		//テキストスクリーンイン
		anim->Move(*text, D3DXVECTOR2(-SCREEN_WIDTH*1.5, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 50.0f, OutCirc);
	},
		[=] {
		//待機
		anim->Wait(5.0f);
	},
		[=] {
		//テキストスクリーンアウト
		anim->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_WIDTH * 1.5, SCREEN_CENTER_Y), 30.0f, InCirc);
	},
		[=] {
		//背景クローズ
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 128.0f), D3DXVECTOR2(SCREEN_WIDTH, 0.0f), 15.0f, OutCirc);
	} };
	anim->SetAnimBehavior(vec);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatResultViewer::~BeatResultViewer()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	SAFE_DELETE(anim);
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatResultViewer::Update()
{
	//再生中なら実行
	if (!isPlaying) return;

	//アニメーション再生
	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying, Callback);
	});
}

//=============================================================================
// 描画処理
//=============================================================================
void BeatResultViewer::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	//背景を先に描画
	bg->Draw();

	//テキスト
	text->Draw();
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void BeatResultViewer::SetTexture(ResultID id)
{
	//テキストのUVを変更
	text->SetTexture(1, ResultID::Max, id);

	//背景のUVを変更
	bg->SetTexture(1, ResultID::Max, id);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
}

//=============================================================================
// 結果ビュアーセット処理
//=============================================================================
void BeatResultViewer::Set(ResultID id, std::function<void(void)> Callback)
{
	//テクスチャ情報受け渡し
	SetTexture(id);

	//再生状態にする
	isPlaying = true;

	//テロップ再生終了通知
	this->Callback = Callback;
}
