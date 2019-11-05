//=============================================================================
//
// Fieldビュアー管理処理 [FieldViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "FieldTelop.h"
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
	fieldViewer.push_back(fieldTelop = new FieldTelop());
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

	if (Keyboard::GetTrigger(DIK_F))
	{
		SetFieldTelop(fieldTelop->City, nullptr);
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
// フィールドテロップを設置
//=============================================================================
void FieldViewer::SetFieldTelop(FieldTelop::TelopID id, std::function<void(void)> Callback)
{
	fieldTelop->Set(id, Callback);
}