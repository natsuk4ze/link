//=============================================================================
//
// 操作説明ビューア処理 [OperationExplanationViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "OperationExplanationViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
OperationExplanationViewer::OperationExplanationViewer()
{
	//テキスト
	for  (int i = 0; i < textMax; i++)
	{
		text[i] = new BaseViewerDrawer();
		text[i]->LoadTexture("data/TEXTURE/Viewer/FieldViewer/OperationExplanationViewer/OperationExplanation.png");
		text[i]->size = D3DXVECTOR3(210.0f, 50.0f, 0.0f);
		text[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		text[i]->position = D3DXVECTOR3((float)(SCREEN_WIDTH/3 + (i*SCREEN_WIDTH/3/2)), SCREEN_CENTER_Y*1.8f, 0.0f);
		text[i]->MakeVertex();

		//初回のセットまで透明にしておく
		text[i]->SetAlpha(0.0f);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
OperationExplanationViewer::~OperationExplanationViewer()
{
	for (int i = 0; i < textMax; i++)
	{
		SAFE_DELETE(text[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void OperationExplanationViewer::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void OperationExplanationViewer::Draw(void)
{
	for (int i = 0; i < textMax; i++)
	{
		text[i]->Draw();
	}
}

//=============================================================================
// テクスチャUVセット処理
//=============================================================================
void OperationExplanationViewer::SetTexture(OperationID id0, OperationID id1, OperationID id2)
{
	//idを格納しておく配列
	OperationID id[textMax] = {
		id0,
		id1,
		id2
	};

	for (int i = 0; i < textMax; i++)
	{
		//IDの種類数ではなく実際のテクスチャ内のテキストの種類でセット
		//表示しないオペレーションなら透明にしておく
		if (id[i] < Z_None)
		{
			const int textTypeMax = 5;

			//テキストのテクスチャUVを変更
			text[i]->SetTexture(1, textTypeMax, id[i]);

			//表示する
			text[i]->SetAlpha(1.0f);
		}
		else
		{
			//透明にしておく
			text[i]->SetAlpha(0.0f);
		}
	}
}

//=============================================================================
// 操作説明ビュアーのセット処理
//=============================================================================
void OperationExplanationViewer::Set(OperationID id0, OperationID id1, OperationID id2)
{
	//テクスチャ情報受け渡し処理
	SetTexture(id0,id1,id2);
}
