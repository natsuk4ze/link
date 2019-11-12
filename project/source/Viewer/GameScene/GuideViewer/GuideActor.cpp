//=====================================
//
// ガイドアクター[GuideViewer.h]
// 機能：ガイド役キャラクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideActor.h"
#include "../../../../Framework/Tool/DebugWindow.h"

//=====================================
// スタティックメンバ初期化
//=====================================
const GuideActor::AnimData GuideActor::data[] = {
	{"Idle", 1.0f, 0.1f, 1 / 30.0f},
	{"Running", 1.0f, 0.1f, 1 / 30.0f}
};

//=====================================
// コンストラクタ
//=====================================
GuideActor::GuideActor()
{
	transform->SetPosition(D3DXVECTOR3(150.0f, 0.0f, -150.0f));
	transform->SetScale(Vector3::One);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// アニメーションの作成
	anim = new AnimationManager();
	anim->LoadXFile("data/MODEL/Boy.x", "Guide");

	// アニメーションセットの作成
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[AnimState(i)].tag, i, data[AnimState(i)].shiftTime);
		anim->SetPlaySpeed(i, data[AnimState(i)].playSpeed);
		anim->SetDeltaTime(i, data[AnimState(i)].deltaTime);
	}

	// アニメーション遷移のセット
	anim->SetFinishTransition(Running, Idle);
	anim->SetFinishTransition(Idle, Idle);
}

//=====================================
// デストラクタ
//=====================================
GuideActor::~GuideActor()
{
	//animのデストラクタは不要
}

//=====================================
// 更新
//=====================================
void GuideActor::Update()
{
	anim->Update();

	Debug::Begin("GuideActor");

	if (Debug::Button("ChangeAnim:Running"))
	{
		anim->ChangeAnim(Running);
	}

	Debug::End();
}

//=====================================
// 描画
//=====================================
void GuideActor::Draw()
{
	if (!IsActive())
		return;

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld();

	anim->Draw(&mtxWorld);
}

//=====================================
// アニメーション切り替え
//=====================================
void GuideActor::ChangeAnim(AnimState next)
{
	anim->ChangeAnim((UINT)next, true);
}
