//=============================================================================
//
// ストック封印ビュアー処理 [SealItemStockViewer.cpp]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../../../Framework/Math/Easing.h"
#include "SealItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// *注意：封印アニメーションと封印解除アニメーションは仕様が決まってないため、
// 暫定的にサイズダウン、フェードアウトを実行。
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//アイコンの初期サイズ
D3DXVECTOR3 initIconSize(400.0f, 400.0f, 0.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
SealItemStockViewer::SealItemStockViewer()
{
	//アイコン
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/EventViewer/SealItemStockViewer/SealIcon.png");
	icon->size = initIconSize;
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
SealItemStockViewer::~SealItemStockViewer()
{
	SAFE_DELETE(icon);
}

//=============================================================================
// 更新処理
//=============================================================================
void SealItemStockViewer::Update(void)
{
	//アニメーション再生制御
	HandlePlayAnim();

	//アニメーション再生
	Play();
}

//=============================================================================
// 描画処理
//=============================================================================
void SealItemStockViewer::Draw(void)
{
	//プレイ中なら描画
	if (!isPlaying) return;

	icon->Draw();
}

//=============================================================================
// 再生処理
//=============================================================================
void SealItemStockViewer::Play(void)
{
	//プレイ中なら実行
	if (!isPlaying) return;

	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / 30.0f;

	//封印された
	if (isSealed)
	{
		//封印アニメーションを再生
		PlaySealAnim();
	}

	//封印が解かれた
	if (isUnSealed)
	{
		//封印解除アニメーションを再生
		PlayUnSealAnim();
	}
}

//=============================================================================
// 封印アニメーション再生処理
//=============================================================================
void SealItemStockViewer::PlaySealAnim(void)
{
	//イージングのスタートとゴールを設定
	float easingStart = 400.0f;
	float easingGoal = 200.0f;

	icon->size.x = Easing::EaseValue(animTime, easingStart, easingGoal, InCubic);
	icon->size.y = Easing::EaseValue(animTime, easingStart, easingGoal, InCubic);

	if (icon->size.y == easingGoal)
	{
		isSealed = false;
	}
}

//=============================================================================
// 封印解除アニメーション再生処理
//=============================================================================
void SealItemStockViewer::PlayUnSealAnim(void)
{
	//イージングのスタートとゴールを設定
	float easingStart = 1.0f;
	float easingGoal = 0.0f;

	//テクスチャのα値
	float alpha;

	alpha = Easing::EaseValue(animTime, easingStart, easingGoal, OutCubic);
	icon->SetAlpha(alpha);

	if (alpha == easingGoal)
	{
		isUnSealed = false;

		//再生終了
		isPlaying = false;
	}
}

//=============================================================================
// 再生制御処理
//=============================================================================
void SealItemStockViewer::HandlePlayAnim(void)
{
	currentParam = parameterBox;

	//前フレームでは封印されてなかったのに現在フレームでは封印されてる
	if (currentParam == true && lastParam == false)
	{
		//封印解除中なら強制終了
		isUnSealed = false;

		//フレームカウントリセット
		countFrame = 0;

		//アイコンのサイズとα値を初期化
		icon->size = initIconSize;
		icon->SetAlpha(1.0f);

		//封印状態に移行
		isSealed = true;

		//再生中に移行
		isPlaying = true;
	}

	//前フレームでは封印されてたのに現在フレームでは封印されてない
	if (currentParam == false && lastParam == true)
	{
		//封印中なら強制終了
		isSealed = false;

		//フレームカウントをリセット
		countFrame = 0;

		//封印解除状態に移行
		isUnSealed = true;
	}

	lastParam = parameterBox;
}
