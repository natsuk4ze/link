//=============================================================================
//
// 連打ゲームスタータービュアー処理 [BeatStarterViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatStarterViewer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//レディーテキスト待機ポジションX
static const float readyTextWaitPosX = SCREEN_WIDTH * 1.5;

//ゴーテキスト待機サイズY
static const float goTextWaitSizeY = 0.0f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BeatStarterViewer::BeatStarterViewer()
{
	//レディーテキスト
	readyText = new BaseViewerDrawer();
	readyText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatStarterViewer/Text.png");
	readyText->size = D3DXVECTOR3(600.0f, 300.0f, 0.0f);
	readyText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	readyText->position = D3DXVECTOR3(readyTextWaitPosX, SCREEN_CENTER_Y, 0.0f);
	readyText->MakeVertex();
	readyText->SetTexture(1, 2, 0);

	//ゴーテキスト
	goText = new BaseViewerDrawer();
	goText->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatStarterViewer/Text.png");
	goText->size = D3DXVECTOR3(600.0f, 0.0f, 0.0f);
	goText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	goText->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	goText->MakeVertex();
	goText->SetTexture(1, 2, 1);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatStarterViewer::~BeatStarterViewer()
{
	SAFE_DELETE(readyText);
	SAFE_DELETE(goText);
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatStarterViewer::Update()
{
	if (shouldReady)
		//レディーテキスト
		InReady();

	if (shouldGo)
		//ゴーテキスト
		InGo();
}

//=============================================================================
// 描画処理
//=============================================================================
void BeatStarterViewer::Draw(void)
{
	if(shouldReady)
		//レディーテキスト
		readyText->Draw();

	if(shouldGo)
		//ゴーテキスト
		goText->Draw();
}

//=============================================================================
// レディーテキストをスクリーンインする処理
//=============================================================================
void BeatStarterViewer::InReady(void)
{
	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / 15.0f;

	//イージングのスタートとゴールを設定
	float readyTextEasingStart = readyTextWaitPosX;
	float readyTextEasingGoal = SCREEN_CENTER_X;

	//レディーテキストの座標を更新
	readyText->position.x = Easing::EaseValue(animTime, readyTextEasingStart, readyTextEasingGoal, OutCirc);
}

//=============================================================================
// ゴーテキストを出現させる処理
//=============================================================================
void BeatStarterViewer::InGo(void)
{
	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / 10.0f;

	//イージングのスタートとゴールを設定
	float goTextEasingStart = goTextWaitSizeY;
	float goTextEasingGoal = 300.0f;

	//ゴーテキストのサイズを更新
	goText->size.y = Easing::EaseValue(animTime, goTextEasingStart, goTextEasingGoal, OutExpo);

	//一定時間経過で消す
	if (countFrame == 50.0f)
	{
		shouldGo = false;
	}
}

//=============================================================================
// レディーテキストセット処理
//=============================================================================
void BeatStarterViewer::SetReady(void)
{
	//ゴーテキストを強制終了
	shouldGo = false;

	//フレーム初期化
	countFrame = 0;

	//アニメーション時間初期化
	animTime = 0;

	//ポジションを待機位置にセット
	readyText->position.x = readyTextWaitPosX;

	//再生状態にする
	shouldReady = true;
}

//=============================================================================
// ゴーテキストセット処理
//=============================================================================
void BeatStarterViewer::SetGo(void)
{
	//レディーテキストを強制終了
	shouldReady = false;

	//フレーム初期化
	countFrame = 0;

	//アニメーション時間初期化
	animTime = 0;

	//サイズを待機サイズにセット
	goText->size.y = goTextWaitSizeY;

	//再生状態にする
	shouldGo = true;
}
