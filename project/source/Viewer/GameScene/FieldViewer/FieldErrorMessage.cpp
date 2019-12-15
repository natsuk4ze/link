//=============================================================================
//
// フィールドエラーメッセージ処理 [FieldErrorMessage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "FieldErrorMessage.h"

#include "../../../../main.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "../../../Sound/SoundConfig.h"
#include "../../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
FieldErrorMessage::FieldErrorMessage()
{
	//テキスト
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/FieldErroMessage/Text.png");
	text->size = D3DXVECTOR3(640.0f, 80.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y*1.3f, 0.0f);
	text->MakeVertex();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
FieldErrorMessage::~FieldErrorMessage()
{
	SAFE_DELETE(text);
}

//=============================================================================
// 更新処理
//=============================================================================
void FieldErrorMessage::Update(void)
{
	//再生中なら実行
	if (!isPlaying) return;

	//フレーム更新
	countFrame++;

	//時間が経過した
	if (countFrame >= 60.0f)
	{
		countFrame = 0;
		isPlaying = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void FieldErrorMessage::Draw(void)
{
	//再生中なら実行
	if (!isPlaying) return;

	//背景を先に描画
	text->Draw();
}

//=============================================================================
// メッセージセット処理
//=============================================================================
void FieldErrorMessage::Set(ErroID id)
{
	//テクスチャ情報受け渡し処理
	text->SetTexture(1, Max, id);

	//再生状態に移行
	isPlaying = true;

	SE::Play(SoundConfig::SEID::Error, 1.0f);
}
