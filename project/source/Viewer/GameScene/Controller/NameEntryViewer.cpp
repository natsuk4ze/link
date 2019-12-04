//=============================================================================
//
// 名前登録ビュアーコントロール処理 [NameEntryViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../NameEntryViewer/NameEntryReelViewer.h"
#include "../NameEntryViewer/NameEntryCursorViewer.h"
#include "../NameEntryViewer/NameEntryInput.h"
#include "NameEntryViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
NameEntryViewer::NameEntryViewer():
	entryNameID(),
	reelCnt()
{
	input = new NameEntryInput();

	nameEntryViewer.push_back(reelViewer = new NameEntryReelViewer());
	nameEntryViewer.push_back(cursorViewer = new NameEntryCursorViewer());
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
NameEntryViewer::~NameEntryViewer()
{
	SAFE_DELETE(input);

	//メモリを解放
	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		SAFE_DELETE(nameEntryViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	nameEntryViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void NameEntryViewer::Update()
{
	if (!isActive)
		return;

#ifdef _DEBUG
	for (int i = 0; i < entryNameMax; i++)
	{
		Debug::Text("nameID%d", entryNameID[i]);
	}
#endif

	MoveCursor();
	UpDownReel();
	SetEntryName();

	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		nameEntryViewer[i]->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void NameEntryViewer::Draw(void)
{
	if (!isActive)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < nameEntryViewer.size(); i++)
	{
		nameEntryViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// 登録名セット処理
//=============================================================================
void NameEntryViewer::SetEntryName()
{
	//エンターボタンが押された
	if (input->GetFinishedEntry())
	{
		//初期化して
		for (int i = 0; i < entryNameMax; i++)
		{
			entryNameID[i] = {};
		}
		//ID格納
		for (int i = 0; i < entryNameMax; i++)
		{
			entryNameID[i] = reelViewer->GetReelChar()[i];
		}
	}
}

//=============================================================================
// カーソルビュアー移動処理
//=============================================================================
void NameEntryViewer::MoveCursor()
{
	//右ボタンが押された
	if (input->GetCursorRight())
	{
		if (reelCnt >= entryNameMax - 1) return;
		cursorViewer->MoveCursorRight();
		reelCnt++;
	}

	//左ボタンが押された
	if (input->GetCursorLeft())
	{
		if (reelCnt <= 0) return;
		cursorViewer->MoveCursorLeft();
		reelCnt--;
	}
}

//=============================================================================
// リールビュアー上下移動処理
//=============================================================================
void NameEntryViewer::UpDownReel()
{
	//上ボタンが押された
	if (input->GetReelUp())
	{
		reelViewer->ReelUp(reelCnt);
	}
	//下ボタンが押された
	if (input->GetReelDown())
	{
		reelViewer->ReelDown(reelCnt);
	}
}

//=============================================================================
// 描画可否判定のセット
//=============================================================================
void NameEntryViewer::SetActive(bool flag)
{
	isActive = flag;
}

//=============================================================================
// 登録名ID取得処理
//=============================================================================
int* NameEntryViewer::GetEntryNameID()
{
	return entryNameID;
}
