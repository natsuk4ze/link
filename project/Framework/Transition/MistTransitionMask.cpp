//=====================================
//
//ミストトランジションマスク処理[MistTransitionMask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "MistTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"

/**************************************
マクロ定義
***************************************/
#define MISTTRANSITION_ALPHAREF_MAX		(255.0f)
#define MISTRANSITION_DURATION			(60)
#define MISTTRANSITION_TEX_NAME			"data/TRANSITION/MistMask.png"

/**************************************
コンストラクタ
***************************************/
MistTransitionMask::MistTransitionMask()
{
	//ポリゴン初期化
	polygon = new Polygon2D();
	polygon->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	polygon->LoadTexture(MISTTRANSITION_TEX_NAME);
	polygon->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));
}

/**************************************
デストラクタ
***************************************/
MistTransitionMask::~MistTransitionMask()
{
	SAFE_DELETE(polygon);
}

/**************************************
更新処理
***************************************/
MaskResult MistTransitionMask::Update()
{
	if (!active)
		return MaskResult::Continuous;

	MaskResult res = MaskResult::Continuous;

	cntFrame++;

	float t = (float)cntFrame / MISTRANSITION_DURATION;
	alphaRef = (DWORD)Easing::EaseValue(t, startRef, endRef, type);

	if (cntFrame == MISTRANSITION_DURATION)
	{
		res = isTransitionOut ? MaskResult::FinishTransitionOut : MaskResult::FinishTransitionIn;
		active = false;
	}

	return res;
}

/**************************************
描画処理
***************************************/
void MistTransitionMask::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//マスク開始
	BeginMask();

	//元のアルファ参照値を保存し切り替え
	DWORD defAlphaRef;
	pDevice->GetRenderState(D3DRS_ALPHAREF, &defAlphaRef);
	pDevice->SetRenderState(D3DRS_ALPHAREF, alphaRef);

	//マスク領域描画
	polygon->Draw();

	//マスク終了
	EndMask();

	//アルファ参照値をもとに戻す
	pDevice->SetRenderState(D3DRS_ALPHAREF, defAlphaRef);
}

/**************************************
セット処理
***************************************/
void MistTransitionMask::Set(bool isOut)
{
	if (active)
		return;

	alphaRef = 0;
	cntFrame = 0;

	active = true;
	isTransitionOut = isOut;

	type = isOut ? EaseType::OutCubic : EaseType::OutCubic;
	startRef = isOut ? MISTTRANSITION_ALPHAREF_MAX : 0;
	endRef = MISTTRANSITION_ALPHAREF_MAX - startRef;
}
