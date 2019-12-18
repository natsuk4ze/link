//=============================================================================
//
// イベントメッセージ処理 [EventMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "EventMessage.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
EventMessage::EventMessage()
{
	//テキスト
	text = new TextViewer("しねきゃぷしょん",40);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->SetPos((int)(SCREEN_WIDTH / 10 * 8.6), (int)(SCREEN_HEIGHT*1.5));

	//背景
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventMessage/BG.png");
	bg->size = D3DXVECTOR3(600.0f, 104.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.4f, SCREEN_HEIGHT*1.5f,0.0f);
	bg->MakeVertex();

	//アニメーション
	anim = new ViewerAnimater();
	const float intervalViewerPos = 100.0f;

	std::vector<std::function<void()>> vec = {
	[=] {
		//背景をスクリーンイン
		anim->Move(*bg, D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT*1.5f),
			D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 40, OutCubic);
	},
	[=] {
		//待機
		anim->Wait(50.0f);
	},
	[=] {
		//背景をスクリーンアウト
		anim->Move(*bg, D3DXVECTOR2(SCREEN_WIDTH / 10 * 8.6f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos),
			D3DXVECTOR2(SCREEN_WIDTH*1.2f, SCREEN_HEIGHT / 10 * 5.5f + (messageSetCnt - 1) * intervalViewerPos), 20, InOutCubic, [=]
		{
			//サブアニメーションでフェードアウト
			anim->SubFade(*bg,1.0f,0.0f,1.5f, InOutCubic);
		});
	} };

	anim->SetAnimBehavior(vec);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
EventMessage::~EventMessage()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
	SAFE_DELETE(anim);
}

//=============================================================================
// 更新処理
//=============================================================================
void EventMessage::Update(void)
{
	//再生中なら実行
	if (!isPlaying) return;

	anim->PlayAnim([=]
	{
		anim->SetPlayFinished(isPlaying);
	});
	text->SetPos((int)bg->GetPosition().x, (int)bg->GetPosition().y);
	text->SetColor(bg->GetColor());
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
// 再生状態取得処理
//=============================================================================
bool EventMessage::GetIsPlaying(void)
{
	return isPlaying;
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

	//開始準備
	text->SetColor(SET_COLOR_NOT_COLORED);
	bg->SetColor(SET_COLOR_NOT_COLORED);

	//再生状態に移行
	isPlaying = true;
}