//=============================================================================
//
// Fieldビュアー管理処理 [FieldViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../FieldViewer/LinkLevelUpViewer.h"
#include "../FieldViewer/FieldErrorMessage.h"
#include "../FieldViewer/OperationExplanationViewer.h"
#include "FieldViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
FieldViewer::FieldViewer()
{
	fieldViewer.push_back(linkLevelUpViewer = new LinkLevelUpViewer());
	fieldViewer.push_back(fieldErroMessage = new FieldErrorMessage());
	fieldViewer.push_back(operationExplanation = new OperationExplanationViewer());
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
FieldViewer::~FieldViewer()
{
	//メモリを解放
	for (unsigned int i = 0; i < fieldViewer.size(); i++)
	{
		SAFE_DELETE(fieldViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	fieldViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void FieldViewer::Update()
{
	for (unsigned int i = 0; i < fieldViewer.size(); i++)
	{
		fieldViewer[i]->Update();
	}

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_O))
	{
		SetOperationExplanation(operationExplanation->X_Cancel, operationExplanation->X_Develop, operationExplanation->X_None);
	}

	if (Keyboard::GetTrigger(DIK_L))
	{
		linkLevelUpViewer->Set(88, nullptr);
	}

	if (Keyboard::GetTrigger(DIK_K))
	{
		linkLevelUpViewer->Set(8, nullptr);
	}

#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void FieldViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (unsigned int i = 0; i < fieldViewer.size(); i++)
	{
		fieldViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// フィールドエラーメッセージを設置
//=============================================================================
void FieldViewer::SetFieldErroMessage(FieldErrorMessage::ErroID id)
{
	fieldErroMessage->Set(id);
}

//=============================================================================
// 上昇した分のリンクレベルを表示する
//=============================================================================
void FieldViewer::ViewLinkLevelUp(int level, std::function<void()> callback)
{
	linkLevelUpViewer->Set(level, callback);
}

//=============================================================================
// 操作説明ビューアを設置
//=============================================================================
void FieldViewer::SetOperationExplanation(
	OperationExplanationViewer::OperationID id1,
	OperationExplanationViewer::OperationID id2,
	OperationExplanationViewer::OperationID id3)
{
	operationExplanation->Set(id1,id2,id3);
}