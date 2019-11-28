//=============================================================================
//
// 名前入力リール処理処理 [NameEntryReelViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Input/input.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "NameEntryReelViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
NameEntryReelViewer::NameEntryReelViewer():
	character()
{
	//リールの座標間隔
	const float intervalReelPos = 130.0f;

	//リール
	for (int i = 0; i < entryNameMax; i++)
	{
		reel[i] = new BaseViewerDrawer();
		reel[i]->LoadTexture("data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Character.png");
		reel[i]->size = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
		reel[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		reel[i]->position = D3DXVECTOR3(SCREEN_CENTER_X + i* intervalReelPos, SCREEN_CENTER_Y, 0.0f);
		reel[i]->MakeVertex();
		reel[i]->SetTexture(6, 6, 0);
	}
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
}

//=============================================================================
// 更新処理
//=============================================================================
void NameEntryReelViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void NameEntryReelViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//背景を先に描画
		reel[i]->Draw();
	}
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
// リールの文字を取得する処理
//=============================================================================
int* NameEntryReelViewer::GetReelChar()
{
	return character;
}