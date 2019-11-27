//=============================================================================
//
// リザルト名前入力処理処理 [ResultNameEntryViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Input/input.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "ResultNameEntryViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static const float intervalPos = 130.0f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
ResultNameEntryViewer::ResultNameEntryViewer():
	charID(),
	charCnt(),
	entryName()
{
	//文字
	for (int i = 0; i < entryNameMax; i++)
	{
		character[i] = new BaseViewerDrawer();
		character[i]->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultNameEntryViewer/Character.png");
		character[i]->size = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
		character[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		character[i]->position = D3DXVECTOR3(SCREEN_CENTER_X + i* intervalPos, SCREEN_CENTER_Y, 0.0f);
		character[i]->MakeVertex();
		character[i]->SetTexture(6, 6, 0);
	}

	//カーソル
	cursor = new BaseViewerDrawer();
	cursor->LoadTexture("data/TEXTURE/Viewer/ResultViewer/ResultNameEntryViewer/Cursor.png");
	cursor->size = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	cursor->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	cursor->MakeVertex();
	cursor->SetTexture(2, 2, 0);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultNameEntryViewer::~ResultNameEntryViewer()
{
	for (int i = 0; i < entryNameMax; i++)
	{
		SAFE_DELETE(character[i]);
	}

	SAFE_DELETE(cursor);
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultNameEntryViewer::Update(void)
{
	//名前入力処理
	NameInput();

	//テクスチャUVセット処理
	SetTexture();

	//カーソルの座標をセット
	SetCursorPos();

	Debug::Text(entryName.c_str());
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultNameEntryViewer::Draw(void)
{
	for (int i = 0; i < entryNameMax; i++)
	{
		//背景を先に描画
		character[i]->Draw();
	}

	cursor->Draw();
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void ResultNameEntryViewer::SetTexture()
{
	//文字盤のテクスチャUVを変更
	character[charCnt]->SetTexture(6, 6, charID[charCnt]);
}

//=============================================================================
// 名前入力処理
//=============================================================================
void ResultNameEntryViewer::NameInput()
{
	//上ボタンが押された
	if (Keyboard::GetTrigger(DIK_UP))
	{
		if (charID[charCnt] > 0)
			charID[charCnt]--;
		else
			charID[charCnt] = charTypeMax-1;
	}
	//下ボタンが押された
	if (Keyboard::GetTrigger(DIK_DOWN))
	{
		if (charID[charCnt] < charTypeMax-1)
			charID[charCnt]++;
		else
			charID[charCnt] = 0;
	}
	//左ボタンが押された
	if (Keyboard::GetTrigger(DIK_LEFT))
	{
		if (charCnt > 0)
			charCnt--;
	}
	//右ボタンが押された
	if (Keyboard::GetTrigger(DIK_RIGHT))
	{
		if (charCnt < entryNameMax-1)
			charCnt++;
	}
	//エンターボタンが押された
	if (Keyboard::GetTrigger(DIK_RETURN))
	{
		entryName = {};

		for (int i = 0; i < entryNameMax; i++)
		{
			SetEntryName(charID[i]);
		}
	}
}

//=============================================================================
// 登録名セット処理
//=============================================================================
void ResultNameEntryViewer::SetEntryName(int id)
{
	std::string charTable[charTypeMax] =
	{
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"!",
		"?",
		"*",
		".",
		"/",
		"\\",
		"#",
		"\"",
		"%%",
		"&"
	};

	entryName += charTable[id];
}

//=============================================================================
// カーソル座標セット処理
//=============================================================================
void ResultNameEntryViewer::SetCursorPos()
{
	cursor->position.x = SCREEN_CENTER_X + charCnt * intervalPos;
}
//=============================================================================
// 登録名取得処理
//=============================================================================
std::string ResultNameEntryViewer::GetEntryName(void)
{
	return entryName;
}