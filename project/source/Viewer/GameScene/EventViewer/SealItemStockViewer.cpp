//=============================================================================
//
// ストック封印ビュアー処理 [SealItemStockViewer.cpp]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "SealItemStockViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Math/Easing.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// *注意：封印アニメーションと封印解除アニメーションは仕様が決まってないため、
// 暫定的にサイズダウン、フェードアウトを実行。
//*****************************************************************************

//アイコンの初期サイズ
const D3DXVECTOR2 initIconSize = D3DXVECTOR2(400.0f, 400.0f);
const float ScaleNum = 0.5f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
SealItemStockViewer::SealItemStockViewer()
{
	//アイコン
	Icon = new TextureDrawer(D3DXVECTOR2(800.0f, 400.0f), 2, 1);
	Icon->LoadTexture("data/TEXTURE/Viewer/EventViewer/SealItemStockViewer/SealIcon.png");
	Icon->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.47f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f));
	Icon->SetIndex(0);

	//アイコン(白)
	Icon_White = new TextureDrawer(D3DXVECTOR2(800.0f, 400.0f), 2, 1, false);
	Icon_White->LoadTexture("data/TEXTURE/Viewer/EventViewer/SealItemStockViewer/SealIcon.png");
	Icon_White->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.47f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f));
	Icon_White->SetIndex(1);
	Icon_White->SetSize(initIconSize * ScaleNum);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
SealItemStockViewer::~SealItemStockViewer()
{
	SAFE_DELETE(Icon);
	SAFE_DELETE(Icon_White);
}

//=============================================================================
// 更新処理
//=============================================================================
void SealItemStockViewer::Update(void)
{
	if (!isPlaying)
		return;

	if (!GetInPause())
	{
		Icon_White->Update();
		Icon->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SealItemStockViewer::Draw(void)
{
	//プレイ中なら描画
	if (!isPlaying)
		return;

	if (!GetInPause())
	{
		Icon_White->Draw();
		Icon->Draw();
	}
}


//=============================================================================
// 封印のカウントダウンを開始
//=============================================================================
void SealItemStockViewer::CountDownStart(void)
{
	Icon_White->Expand(285.0f, ExpandType::ExpandUpToDown);
	Icon->Close(285.0f, CloseType::CloseUpToDown, EaseType::Linear, [&]()
	{
		isPlaying = false;
	});
}

//=============================================================================
// ストック封印アイコンを設置する
//=============================================================================
void SealItemStockViewer::SetBanIcon(std::function<bool(void)> func)
{
	// 初期化
	GetInPause = func;
	isPlaying = true;
	Icon->Reset();
	Icon->SetSize(initIconSize);
	Icon->SetVisible(true);
	Icon_White->Reset();
	Icon_White->SetVisible(false);

	Icon->SetScale(15.0f, 0.5f, EaseType::Linear, [&]()
	{
		CountDownStart();
	});
}

//=============================================================================
// ビュアーのリセット
//=============================================================================
void SealItemStockViewer::Reset(void)
{
	isPlaying = false;
	Icon->SetSize(initIconSize);
	Icon->SetVisible(false);
	Icon_White->SetVisible(false);
}
