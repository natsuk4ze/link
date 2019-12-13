//=============================================================================
//
// 名前入力リール処理処理 [NameEntryReelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "NameEntryReelViewer.h"

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include"../../Framework/ViewerAnimater/ViewerAnimater.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//リールの座標間隔
static const float intervalReelPos = 166.50f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
NameEntryReelViewer::NameEntryReelViewer() :
	isInPlaying(false),
	isOutPlaying(false)
{
	const D3DXVECTOR2 cursorPos = { SCREEN_WIDTH / 10 * 6.6250f, SCREEN_HEIGHT / 1.520f };
	const D3DXVECTOR2 bgPos = { SCREEN_WIDTH / 10 * 7.50f, SCREEN_HEIGHT / 1.250f };
	const D3DXVECTOR2 textPos = { (int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.250f) };
	const D3DXVECTOR2 underBarPos = { (int)(SCREEN_WIDTH / 10 * 7.50f), (int)(SCREEN_HEIGHT / 1.45f) };
	const float animStartPosX = SCREEN_WIDTH * 1.50f;

	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i] = new BaseViewerDrawer(D3DXVECTOR2(animStartPosX + i * intervalReelPos, SCREEN_HEIGHT / 1.520f),
			D3DXVECTOR2(180.0f, 180.0f), "data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Character.png");
		reel[i]->SetTexture(6, 6, 0);
	}

	cursor = new BaseViewerDrawer(D3DXVECTOR2(animStartPosX, cursorPos.y),
		D3DXVECTOR2(150.0f, 150.0f), "data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Cursor.png");

	bg = new BaseViewerDrawer(D3DXVECTOR2(animStartPosX, bgPos.y), D3DXVECTOR2(600.0f, 512.0f / 4),
		"data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/BG.png");

	text = new TextViewer("data/FONT/Makinas-4-Square.otf", 50);
	text->SetPos((int)(animStartPosX), (int)textPos.y);
	text->SetText("名前を入力してね");

	underBar = new TextViewer("data/FONT/Makinas-4-Square.otf", 100);
	underBar->SetPos((int)(animStartPosX), (int)underBarPos.y);
	underBar->SetText("＿　＿　＿");

	anim[AnimScene::TelopIn] = new ViewerAnimater();
	std::vector<std::function<void()>> inVec = { [=]
	{
		InReel([=]
		{
			anim[AnimScene::TelopIn]->SubMove(*cursor, D3DXVECTOR2(animStartPosX, cursorPos.y),cursorPos,OutCirc,[=]
			{
				anim[AnimScene::TelopIn]->SubMove(*bg, D3DXVECTOR2(animStartPosX, bgPos.y),bgPos,OutCirc);
			});
		});
	}
	};
	anim[AnimScene::TelopIn]->SetAnimBehavior(inVec);

	anim[AnimScene::TelopOut] = new ViewerAnimater();
	std::vector<std::function<void()>> outVec = { [=]
	{
		OutReel([=]
		{
			anim[AnimScene::TelopOut]->SubMove(*cursor,cursorPos,D3DXVECTOR2(animStartPosX, cursorPos.y),InCirc,[=]
			{
				anim[AnimScene::TelopOut]->SubMove(*bg,bgPos,D3DXVECTOR2(animStartPosX, bgPos.y),InCirc);
			});
		});
	}
	};
	anim[AnimScene::TelopOut]->SetAnimBehavior(outVec);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
NameEntryReelViewer::~NameEntryReelViewer()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		SAFE_DELETE(reel[i]);
	}
	SAFE_DELETE(cursor);
	SAFE_DELETE(bg);
	SAFE_DELETE(text);
	SAFE_DELETE(underBar);
	SAFE_DELETE(anim[AnimScene::TelopIn]);
	SAFE_DELETE(anim[AnimScene::TelopOut]);
}

//=============================================================================
// 更新処理
//=============================================================================
void NameEntryReelViewer::Update(void)
{
	if (isInPlaying)
	{
		anim[AnimScene::TelopIn]->PlayAnim([=]
		{
			anim[AnimScene::TelopIn]->SetPlayFinished(isInPlaying);
		});
	}
	if (isOutPlaying)
	{
		anim[AnimScene::TelopOut]->PlayAnim([=]
		{
			anim[AnimScene::TelopOut]->SetPlayFinished(isOutPlaying);
		});
	}
	text->SetPos((int)bg->position.x, (int)bg->position.y);
	underBar->SetPos((int)bg->position.x, (int)(SCREEN_HEIGHT / 1.45f));
}

//=============================================================================
// 描画処理
//=============================================================================
void NameEntryReelViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i]->Draw();
	}
	cursor->Draw();
	bg->Draw();
	text->Draw();
	underBar->Draw();
}

//=============================================================================
// リールのスクリーンイン処理
//=============================================================================
void NameEntryReelViewer::InReel(std::function<void()> Callback)
{
	const float animStartPosX = SCREEN_WIDTH * 1.50f;
	int index = 0;
	anim[AnimScene::TelopIn]->Move(*reel[index], D3DXVECTOR2(animStartPosX, reel[index]->position.y),
		D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y), 20.0f, OutCirc, [=]
	{
		int index = 1;
		anim[AnimScene::TelopIn]->SubMove(*reel[index], D3DXVECTOR2(animStartPosX, reel[index]->position.y),
			D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y), OutCirc, [=]
		{
			int index = 2;
			anim[AnimScene::TelopIn]->SubMove(*reel[index], D3DXVECTOR2(animStartPosX, reel[index]->position.y),
				D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y), OutCirc, [=]
			{
				Callback();
			});
		});
	});
}

//=============================================================================
// リールのスクリーンアウト処理
//=============================================================================
void NameEntryReelViewer::OutReel(std::function<void()> Callback)
{
	const float animStartPosX = SCREEN_WIDTH * 1.50f;
	int index = 0;
	anim[AnimScene::TelopOut]->Move(*reel[index], D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y),
		D3DXVECTOR2(animStartPosX, reel[index]->position.y), 20.0f, InCirc, [=]
	{
		int index = 1;
		anim[AnimScene::TelopOut]->SubMove(*reel[index], D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y),
			D3DXVECTOR2(animStartPosX, reel[index]->position.y), InCirc, [=]
		{
			int index = 2;
			anim[AnimScene::TelopOut]->SubMove(*reel[index], D3DXVECTOR2(SCREEN_WIDTH / 10 * 6.6250f + index * intervalReelPos, reel[index]->position.y),
				D3DXVECTOR2(animStartPosX, reel[index]->position.y), InCirc, [=]
			{
				Callback();
			});
		});
	});
}

//=============================================================================
// リールアップ処理
//=============================================================================
void NameEntryReelViewer::ReelUp(int reelCnt)
{
	if (character[reelCnt] > 0)
		character[reelCnt]--;
	else
		character[reelCnt] = charTypeMax - 1;

	//リールのテクスチャUVを変更
	reel[reelCnt]->SetTexture(6, 6, character[reelCnt]);
}

//=============================================================================
// リールダウン処理
//=============================================================================
void NameEntryReelViewer::ReelDown(int reelCnt)
{
	if (character[reelCnt] < charTypeMax - 1)
		character[reelCnt]++;
	else
		character[reelCnt] = 0;

	//リールのテクスチャUVを変更
	reel[reelCnt]->SetTexture(6, 6, character[reelCnt]);
}

//=============================================================================
// カーソル右移動処理
//=============================================================================
void NameEntryReelViewer::MoveCursorRight(void)
{
	cursor->position.x += intervalReelPos;
}

//=============================================================================
// カーソル左移動処理
//=============================================================================
void NameEntryReelViewer::MoveCursorLeft(void)
{
	cursor->position.x -= intervalReelPos;
}

//=============================================================================
// リールの文字を取得する処理
//=============================================================================
int* NameEntryReelViewer::GetReelChar()
{
	return character;
}

//=============================================================================
// テロップスクリーンイン処理
//=============================================================================
void NameEntryReelViewer::SetTelopIn()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//文字列初期化
		character[i] = 0;
		// UVの初期化
		reel[i]->SetTexture(6, 6, 0);
	}

	isInPlaying = true;
}

//=============================================================================
// テロップスクリーンアウト処理
//=============================================================================
void NameEntryReelViewer::SetTelopOut()
{
	isOutPlaying = true;
}