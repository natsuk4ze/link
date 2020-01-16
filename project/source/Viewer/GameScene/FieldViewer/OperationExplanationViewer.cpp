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
OperationExplanationViewer::OperationExplanationViewer() :
	active(true)
{
	//テキスト
	const D3DXVECTOR3 Size = { 250.0f, 62.5f, 0.0f };
	const D3DXVECTOR3 BasePosition = { SCREEN_CENTER_X - Size.x * 1.5f, 960.0f, 0.0f };
	for (int i = 0; i < textMax; i++)
	{

		text[i] = new BaseViewerDrawer();
		text[i]->LoadTexture("data/TEXTURE/Viewer/FieldViewer/OperationExplanationViewer/OperationExplanation.png");
		text[i]->size = Size;
		text[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		D3DXVECTOR3 position = BasePosition;
		position.x += Size.x * i;
		text[i]->position = position;
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
	if (!active)
		return;

	for (int i = 0; i < textMax; i++)
	{
		text[i]->Draw();
	}
}

//=============================================================================
// テクスチャUVセット処理
//=============================================================================
void OperationExplanationViewer::SetTexture(OperationID id0, OperationID id1, OperationID id2, OperationID id3)
{
	//idを格納しておく配列
	OperationID id[textMax] = {
		id0,
		id1,
		id2,
		id3
	};

	for (int i = 0; i < textMax; i++)
	{
		//IDの種類数ではなく実際のテクスチャ内のテキストの種類でセット
		//表示しないオペレーションなら透明にしておく
		if (id[i] < Z_None)
		{
			const int textTypeMax = 7;

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
void OperationExplanationViewer::Set(OperationID id0, OperationID id1, OperationID id2, OperationID id3)
{
	//テクスチャ情報受け渡し処理
	SetTexture(id0, id1, id2, id3);
}

//=============================================================================
// アクティブ設定
//=============================================================================
void OperationExplanationViewer::SetActive(bool state)
{
	active = state;
}
