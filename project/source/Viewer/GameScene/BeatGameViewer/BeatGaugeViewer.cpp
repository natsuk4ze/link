//=============================================================================
//
// 連打ゲームゲージビュアー処理 [BeatGaugeViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "BeatGaugeViewer.h"

#ifdef _DEBUG

#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"

#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
BeatGaugeViewer::BeatGaugeViewer()
{
	//バー
	bar = new BaseViewerDrawer();
	bar->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatGaugeViewer/Gauge01.png");
	bar->size = D3DXVECTOR3(1300.0f, 120.0f, 0.0f);
	bar->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bar->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/3*2.40f, 0.0f);
	bar->MakeVertex();
	bar->SetTexture(1, 2, 1);

	//フレーム
	frame = new BaseViewerDrawer();
	frame->LoadTexture("data/TEXTURE/Viewer/BeatGameViewer/BeatGaugeViewer/Gauge01.png");
	frame->size = D3DXVECTOR3(1600.0f, 120.0f, 0.0f);
	frame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frame->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_HEIGHT/3*2.40f, 0.0f);
	frame->MakeVertex();
	frame->SetTexture(1, 2, 2);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BeatGaugeViewer::~BeatGaugeViewer()
{
	SAFE_DELETE(bar);
	SAFE_DELETE(frame);
}

//=============================================================================
// 更新処理
//=============================================================================
void BeatGaugeViewer::Update()
{
	//振動制御
	HandleShake();
}

//=============================================================================
// 描画処理
//=============================================================================
void BeatGaugeViewer::Draw(void)
{
	//バーを先に描画
	DrawBar();

	//フレーム
	frame->Draw();
}

//=============================================================================
// 振動制御処理
//=============================================================================
void BeatGaugeViewer::HandleShake()
{
	//とりあえずパラメータの差で実装
	currentParam = gaugePer;

	if (currentParam < lastParam)
	{
		shouldShake = true;
	}

	lastParam = gaugePer;

	//振動させるべきなら実行
	if (shouldShake)
	{
		Shake();
	}
}

//=============================================================================
// 振動処理
//=============================================================================
void BeatGaugeViewer::Shake()
{
	//何回振動させるか
	const int shakeNum = 400;
	//どのくらいの振れ幅か
	const float shakeValue = 3.0f;
	//どのくらいの時間振動させるか
	const float shakeTime = 2.0f;
	//初期座標
	const float initPosX = SCREEN_CENTER_X;
	const float initPosY = SCREEN_HEIGHT / 3 * 2.40f;
	//イージングのスタートとゴールを設定
	const float easingStart = 0.0f;
	const float easingGoal = D3DX_PI * shakeNum;

	countFrame++;
	animTime = countFrame / shakeTime;

	radian = Easing::EaseValue(animTime, easingStart, easingGoal, OutCirc);

	frame->position.x = initPosX + shakeValue * sinf(radian);
	frame->position.y = initPosY + shakeValue * sinf(radian);

	if (radian >= easingGoal)
	{
		//座標を初期化
		frame->position.x = initPosX;
		frame->position.y = initPosY;

		radian = 0.0f;
		countFrame = 0;
		animTime = 0;
		shouldShake = false;
	}
}

//=============================================================================
// ゲージバー描画処理
//=============================================================================
void BeatGaugeViewer::DrawBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	bar->vertexWk[0].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2, -bar->size.y / 2, 0.0f);
	bar->vertexWk[1].vtx = bar->position + D3DXVECTOR3(-bar->size.x/2 + (bar->size.x*gaugePer), -bar->size.y / 2, 0.0f);
	bar->vertexWk[2].vtx = bar->position + D3DXVECTOR3(-bar->size.x / 2, bar->size.y / 2, 0.0f);
	bar->vertexWk[3].vtx = bar->position + D3DXVECTOR3(-bar->size.x/2 + (bar->size.x*gaugePer), bar->size.y / 2, 0.0f);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, bar->texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, bar->vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ゲージセット処理
//=============================================================================
void BeatGaugeViewer::Set(float percent)
{
	//ゲージ割合をセット
	gaugePer = percent;
}
