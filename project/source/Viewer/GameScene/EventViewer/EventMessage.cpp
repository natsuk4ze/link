//=============================================================================
//
// イベントメッセージ処理 [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "EventMessage.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//アニメーションの数
static const int animMax = 3;

//ビュアーの表示座標間隔
static const float intervalViewerPos = 100.0f;

//アニメーション開始位置
static const D3DXVECTOR2 animStartPosition[animMax] = {
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT*1.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT/10*5.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT / 10 * 5.5)),
};

//アニメーション終了位置
static const D3DXVECTOR2 animEndPosition[animMax] = {
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT / 10 * 5.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH / 10 * 8.6),(float)(SCREEN_HEIGHT / 10 * 5.5)),
	D3DXVECTOR2((float)(SCREEN_WIDTH*1.2),(float)(SCREEN_HEIGHT / 10 * 5.5)),
};

//アニメーション種類
static const EaseType animType[animMax] = {
	InOutCubic,
	InOutCubic,
	InOutCubic,
};

//アニメーション間隔
static const float animDuration[animMax] = {
	50,
	50,
	30,
};

//アニメーションシーン
enum animScene
{
    In,
	Stop,
	Out
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventMessage::EventMessage() :
	currentAnim(0)
{
	//テキスト
	text = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf",40);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 8.6), (int)(SCREEN_HEIGHT*1.5));

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventMessage/BG.png");
	bg->size = D3DXVECTOR3(560.0f, 104.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 8.6), (float)(SCREEN_HEIGHT*1.5),0.0f);
	bg->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventMessage::Update(void)
{
	//再生処理
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void EventMessage::Draw(void)
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
void EventMessage::Play(void)
{
	//再生中なら実行
	if (!isPlaying) return;
	
	//ポジション
	D3DXVECTOR2 position;
	
	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / animDuration[currentAnim];

	//ポジションを更新
	position = Easing::EaseValue(animTime,
	animStartPosition[currentAnim],
	animEndPosition[currentAnim],
	animType[currentAnim]);

	//アニメーション更新
	if (countFrame == animDuration[currentAnim])
	{
		countFrame = 0;
		currentAnim++;
	}

	//Outシーン以降はフェードアウトを実行
	if (currentAnim >= Out)
	{
		FadeOut();
	}

	//アニメーション終了
	if (currentAnim == animMax)
	{
		countFrame = 0;
		currentAnim = 0;
		animTime = 0;
		alpha = 1.0f;
		text->SetColor(SET_COLOR_NOT_COLORED);
		bg->SetColor(SET_COLOR_NOT_COLORED);
		isPlaying = false;
	}

	//ポジションをセット(*後に変更予定)
	text->SetPos((int)position.x,(int)position.y + int((messageSetCnt-1) * intervalViewerPos));
	bg->position = D3DXVECTOR3(position.x, position.y + (messageSetCnt-1) * intervalViewerPos, 0.0f);
}

//=============================================================================
// フェードアウト処理
//=============================================================================
void EventMessage::FadeOut(void)
{
	//α値の最小を0.0fに設定
	alpha = Math::Max(alpha, 0.0f);

	//フェードアウト中はα値を減算
	alpha -= 0.05f;

	text->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	bg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}

//=============================================================================
// メッセージセット処理
//=============================================================================
void EventMessage::SetEventMessage(const std::string &message, int &cnt)
{
	//メッセージカウントをセット
	messageSetCnt = cnt;

	//テキストにメッセージをセット
	text->SetText(message);

	//再生状態に移行
	isPlaying = true;
}
