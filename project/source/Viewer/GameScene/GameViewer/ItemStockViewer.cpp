//=============================================================================
//
// ストックビュアー処理 [ItemStockViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../Framework/ViewerDrawer/CountViewerDrawer.h"
#include "../../../../Framework/Math/Easing.h"
#include "ItemStockViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************
// ストック使用禁止効果の継続フレーム
// 本来は300フレームのはずだが、登場演出の30フレームを減らさないと演出がずれじゃう
static const int DefaultDebuffCount = 270;

//数字のホップ量
static const float hopNumValue = 30.0f;

//数字の初期サイズ
static const D3DXVECTOR3 initNumSize = D3DXVECTOR3(42.0f, 42.0f, 0.0f);

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ItemStockViewer::ItemStockViewer() :
	InBanStock(false)
{
	//数字
	num = new CountViewerDrawer();
	num->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	num->MakeVertex();
	num->size = initNumSize;
	num->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	num->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.21f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	num->SetColor(SET_COLOR_NOT_COLORED);
	num->intervalNumberScr = 42.0f;
	num->intervalNumberTex = 0.10f;
	num->placeMax = 2;
	num->baseNumber = 10;
	num->isHopped = false;
	num->radian = 0;

	//ストックアイコン
	icon = new BaseViewerDrawer();
	icon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Drill.png");
	icon->MakeVertex();
	icon->size = D3DXVECTOR3(180.0f, 135.0f, 0.0f);
	icon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	icon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.7f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	icon->SetColor(SET_COLOR_NOT_COLORED);

	//バツアイコン
	BanIcon = new BaseViewerDrawer();
	BanIcon->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock.png");
	BanIcon->size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	BanIcon->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BanIcon->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	BanIcon->SetColor(SET_COLOR_NOT_COLORED);
	BanIcon->MakeVertex();

	//バツアイコン
	BanIcon_White = new BaseViewerDrawer();
	BanIcon_White->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/BanStock_White.png");
	BanIcon_White->size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	BanIcon_White->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BanIcon_White->position = D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.5f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f);
	BanIcon_White->SetColor(SET_COLOR_NOT_COLORED);
	BanIcon_White->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ItemStockViewer::~ItemStockViewer()
{
	SAFE_DELETE(num);
	SAFE_DELETE(icon);
	SAFE_DELETE(BanIcon);
	SAFE_DELETE(BanIcon_White);
}

//=============================================================================
// 更新処理
//=============================================================================
void ItemStockViewer::Update(void)
{
	//アニメーション
	Animate();
}

//=============================================================================
// 描画処理
//=============================================================================
void ItemStockViewer::Draw(void)
{
	//アイコン
	icon->SetVertex();
	icon->Draw();

	//数字
	num->DrawCounter(num->baseNumber, parameterBox, num->placeMax,
		num->intervalNumberScr, num->intervalNumberTex);

	// バツアイコン
	if (InBanStock)
	{
		BanIcon_White->Draw();
		BanIcon->Draw();
	}
}

//=============================================================================
// アニメーション処理
//=============================================================================
void ItemStockViewer::Animate(void)
{
	//現在のパラメータ
	static int currentParam;

	//１フレーム前のパラメータ
	static int lastParam;

	static int FrameCount = 0;

	//前フレームのパラメータとの差が0でないときホッピング状態にする
	currentParam = parameterBox;
	if (currentParam - lastParam != 0)
	{
		num->isHopped = true;
	}
	lastParam = parameterBox;

	//ホッピング処理
	num->size.y = num->HopNumber(num->size.y, initNumSize.y, hopNumValue);

	if (InBanStock)
	{
		if (BanIconDebut)
		{
			// バツアイコン登場の演出
			FrameCount++;

			float Size = Easing::EaseValue((float)FrameCount / 30, 200.0f, 100.0f, InExpo);

			if (Size <= 100.0f)
			{
				FrameCount = DefaultDebuffCount;
				BanIconDebut = false;
			}

			BanIcon->size = D3DXVECTOR3(Size, Size, 0.0f);
			BanIcon_White->size = D3DXVECTOR3(Size, Size, 0.0f);
			// BaseViewerDrawerの頂点設置関数
			BanIcon->SetVertex();
			BanIcon_White->SetVertex();
		}
		else
		{
			float RemainTimePercent = (float)FrameCount / (float)DefaultDebuffCount;
			float Percent = Easing::EaseValue((1 - RemainTimePercent), 1.0f, -1.0f, EaseType::Linear);

			FrameCount--;
			// ItemStockViewerの頂点設置関数、効果が違う
			SetBanIconVertex(Percent);
			SetBanIconTexture(RemainTimePercent);
		}
	}
}

//=============================================================================
// バツアイコンの頂点情報設定
//=============================================================================
void ItemStockViewer::SetBanIconVertex(float Percent)
{
	BanIcon->vertexWk[0].vtx = BanIcon->position + D3DXVECTOR3(-BanIcon->size.x, -BanIcon->size.y * Percent, 0.0f);
	BanIcon->vertexWk[1].vtx = BanIcon->position + D3DXVECTOR3(BanIcon->size.x, -BanIcon->size.y * Percent, 0.0f);
	BanIcon->vertexWk[2].vtx = BanIcon->position + D3DXVECTOR3(-BanIcon->size.x, BanIcon->size.y, 0.0f);
	BanIcon->vertexWk[3].vtx = BanIcon->position + D3DXVECTOR3(BanIcon->size.x, BanIcon->size.y, 0.0f);

	BanIcon_White->vertexWk[0].vtx = BanIcon_White->position + D3DXVECTOR3(-BanIcon_White->size.x, -BanIcon_White->size.y, 0.0f);
	BanIcon_White->vertexWk[1].vtx = BanIcon_White->position + D3DXVECTOR3(BanIcon_White->size.x, -BanIcon_White->size.y, 0.0f);
	BanIcon_White->vertexWk[2].vtx = BanIcon_White->position + D3DXVECTOR3(-BanIcon_White->size.x, BanIcon_White->size.y * -Percent, 0.0f);
	BanIcon_White->vertexWk[3].vtx = BanIcon_White->position + D3DXVECTOR3(BanIcon_White->size.x, BanIcon_White->size.y * -Percent, 0.0f);
}

//=============================================================================
// バツアイコンのテクスチャ情報設定
//=============================================================================
void ItemStockViewer::SetBanIconTexture(float Percent)
{
	BanIcon->vertexWk[0].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	BanIcon->vertexWk[1].tex = D3DXVECTOR2(1.0f, (1 - Percent));
	BanIcon->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	BanIcon->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	BanIcon_White->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	BanIcon_White->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	BanIcon_White->vertexWk[2].tex = D3DXVECTOR2(0.0f, (1 - Percent));
	BanIcon_White->vertexWk[3].tex = D3DXVECTOR2(1.0f, (1 - Percent));
}