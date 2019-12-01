//=============================================================================
//
// イベントテロップ処理 [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "EventTelop.h"

#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventTelop::EventTelop():
	animArray(),
	isPlaying(false)
{
	//テキスト
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/Text/Text.png");
	text->size = D3DXVECTOR3(1024, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.5, SCREEN_CENTER_Y, 0.0f);
	text->MakeVertex();

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/BG/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->MakeVertex();

	//アニメーション
	anim = new ViewerAnimater();
	SetAnimBehavior();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	SAFE_DELETE(anim);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventTelop::Update()
{
	//再生中なら実行
	if (!isPlaying) return;

	//アニメーション再生
	anim->PlayAnim(animArray, [=]
	{
		SetPlayFinished();
	});
}

//=============================================================================
// 描画処理
//=============================================================================
void EventTelop::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	//背景を先に描画
	bg->Draw();

	//テキスト
	text->Draw();
}

//=============================================================================
// アニメーションの動作設定処理
//=============================================================================
void EventTelop::SetAnimBehavior(void)
{
	//アニメーション配列にアニメーションをセット
	animArray.push_back([=]()
	{
		//背景オープン
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, 128.0f), 15.0f, OutCirc);
	});
	animArray.push_back([=]()
	{
		//テキストスクリーンイン
		anim->Move(*text, D3DXVECTOR2(SCREEN_WIDTH*1.5, SCREEN_CENTER_Y), D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), 50.0f, OutCirc);
	});
	animArray.push_back([=]()
	{
		//待機
		anim->Wait(5.0f);
	});
	animArray.push_back([=]()
	{
		//テキストスクリーンアウト
		anim->Move(*text, D3DXVECTOR2(SCREEN_CENTER_X, SCREEN_CENTER_Y), D3DXVECTOR2(-SCREEN_WIDTH * 1.5, SCREEN_CENTER_Y), 30.0f, InCirc);
	});
	animArray.push_back([=]()
	{
		//背景クローズ
		anim->Scale(*bg, D3DXVECTOR2(SCREEN_WIDTH, 128.0f), D3DXVECTOR2(SCREEN_WIDTH, 0.0f), 15.0f, OutCirc);
	});
}

//=============================================================================
// アニメーション終了処理
//=============================================================================
bool EventTelop::SetPlayFinished(void)
{
	if (Callback != nullptr)
		Callback();

	return isPlaying = false;
}

//=============================================================================
// テクスチャUVセット処理
//=============================================================================
void EventTelop::SetTexture(TelopID id)
{
	//テキストのUVを変更
	text->SetTexture(1, Max, id);

	bool isNegative;

	if (id >= Meteorite) isNegative = true;
	else isNegative = false;

	//背景のUVを変更
	bg->SetTexture(1, 2, isNegative);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
}


//=============================================================================
// テロップセット処理
//=============================================================================
void EventTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//テクスチャ情報受け渡し
	SetTexture(id);

	//再生状態にする
	isPlaying = true;

	//テロップ再生終了通知
	this->Callback = Callback;
}
