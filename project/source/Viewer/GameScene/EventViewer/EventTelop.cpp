//=============================================================================
//
// イベントテロップ処理 [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "EventTelop.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventTelop::EventTelop()
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

	//アニメーションの動作を設定
	SetAnimBehavior();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventTelop::Update()
{
	//再生中なら実行
	if (!isPlaying) return;

	//アニメーション再生
	ViewerAnimater::PlayAnim(animArray, [=]
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
	//アニメーションの数
	const int animMax = 5;

	const D3DXVECTOR2 textStartPosition[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH*1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_WIDTH*1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(-SCREEN_WIDTH * 1.5,SCREEN_CENTER_Y),
	};

	const D3DXVECTOR2 textEndPosition[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH*1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(SCREEN_CENTER_X,SCREEN_CENTER_Y),
		D3DXVECTOR2(-SCREEN_WIDTH * 1.5,SCREEN_CENTER_Y),
		D3DXVECTOR2(-SCREEN_WIDTH * 1.5,SCREEN_CENTER_Y),
	};

	const D3DXVECTOR2 bgStartSize[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
	};

	const D3DXVECTOR2 bgEndSize[animMax] =
	{
		D3DXVECTOR2(SCREEN_WIDTH, 128.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH, 0.0f),
	};


	//テキストアニメーション種類
	const EaseType animType[animMax] = {
		OutCirc,
		OutCirc,
		InOutCubic,
		InCirc,
		OutCirc
	};

	//テキストアニメーション間隔(ここを変更するとアニメーションの速さを調整できる)
	//*注意(0を入れると無限大になるからアニメーションそのものを削除すること)
	const float animDuration[animMax] = {
		15,
		50,
		5,
		30,
		15
	};

	//アニメーションシーン
	enum TelopAnimScene
	{
		BG_Open,
		Text_In,
		Text_Stop,
		Text_Out,
		BG_Close
	};

	//アニメーション配列にアニメーションをセット
	animArray.push_back([=]()
	{
		//背景オープン
		ViewerAnimater::Scale(*bg, bgStartSize[BG_Open], bgEndSize[BG_Open], animDuration[BG_Open], animType[BG_Open]);
	});
	animArray.push_back([=]()
	{
		//テキストスクリーンイン
		ViewerAnimater::Move(*text, textStartPosition[Text_In], textEndPosition[Text_In], animDuration[Text_In], animType[Text_In]);
	});
	animArray.push_back([=]()
	{
		//待機
		ViewerAnimater::Wait(animDuration[Text_Stop]);
	});
	animArray.push_back([=]()
	{
		//テキストスクリーンアウト
		ViewerAnimater::Move(*text, textStartPosition[Text_Out], textEndPosition[Text_Out], animDuration[Text_Out], animType[Text_Out]);
	});
	animArray.push_back([=]()
	{
		//背景クローズ
		ViewerAnimater::Scale(*bg, bgStartSize[BG_Close], bgEndSize[BG_Close], animDuration[BG_Close], animType[BG_Close]);
	});
}

//=============================================================================
// アニメーション終了処理
//=============================================================================
bool EventTelop::SetPlayFinished(void)
{
	if (Callback != nullptr)
	{
		//再生終了の通知
		Callback();
	}

	return isPlaying = false;
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void EventTelop::SetTexture(TelopID id)
{
	//テキストのUVを変更
	text->SetTexture(1, Max, id);

	bool isNegative;

	if (id >= Meteorite)
	{
		isNegative = true;
	}
	else
	{
		isNegative = false;
	}

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
