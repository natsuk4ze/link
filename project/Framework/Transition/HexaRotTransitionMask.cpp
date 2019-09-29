//=====================================
//
//ヘキサトランジション処理[HexaRotTransitionMask.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "HexaRotTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"
#include "../Tween/Tween.h"

/**************************************
マクロ定義
***************************************/
#define HEXATRANSITION_DURATION		(60)

/**************************************
コンストラクタ
***************************************/
HexaRotTransitionMask::HexaRotTransitionMask()
{
	//ポリゴン初期化
	hex = new RotationHexa();
	hex->LoadTexture("data/TRANSITION/HexaMask.png");
	hex->SetSize((float)SCREEN_WIDTH, (float)SCREEN_WIDTH);
	hex->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));
}

/**************************************
デストラクタ
***************************************/
HexaRotTransitionMask::~HexaRotTransitionMask()
{
	SAFE_DELETE(hex);
}

/**************************************
更新処理
***************************************/
MaskResult HexaRotTransitionMask::Update()
{
	if (!active)
		return Continuous;

	MaskResult result = MaskResult::Continuous;

	cntFrame++;

	hex->Update();

	//トランジションの終了確認
	if (cntFrame == HEXATRANSITION_DURATION)
	{
		//マスクをオフに
		active = false;
		
		result = isTransitionOut ? FinishTransitionOut : FinishTransitionIn;
	}
	return result;
}

/**************************************
トランジション開始処理
***************************************/
void HexaRotTransitionMask::Draw()
{
	if (!active)
		return;

	BeginMask();

	hex->Draw();

	EndMask();
}

/**************************************
トランジション開始処理
***************************************/
void HexaRotTransitionMask::Set(bool isTransitionOut)
{
	//すでにマスク中であれば開始しない
	if (active)
		return;

	//イージング開始
	hex->Init(isTransitionOut);

	//フラグ初期化
	cntFrame = 0;
	active = true;
	this->isTransitionOut = isTransitionOut;
}

/**************************************
回転六角形初期化処理
***************************************/
void RotationHexa::Init(bool isTransitionOut)
{
	const D3DXVECTOR3 InitScale = isTransitionOut ? Vector3::Zero : Vector3::One;
	const D3DXVECTOR3 EndScale = Vector3::One - InitScale;
	const EaseType Type = isTransitionOut ? EaseType::InExpo : EaseType::OutExpo;

	Tween::Scale(*this, InitScale, EndScale, HEXATRANSITION_DURATION, Type);
}

/**************************************
回転六角形更新処理
***************************************/
void RotationHexa::Update()
{
	transform->Rotate(0.0f, 0.0f, 10.0f);
}