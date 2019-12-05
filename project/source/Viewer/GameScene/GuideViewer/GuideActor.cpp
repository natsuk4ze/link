//=====================================
//
// ガイドアクター[GuideViewer.h]
// 機能：ガイド役キャラクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GuideActor.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Tween/Tween.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../../Framework/Particle/BaseEmitter.h"

//=====================================
// スタティックメンバ初期化
//=====================================
const GuideActor::AnimData GuideActor::data[] = {
	{"Idle", 1.0f, 0.3f, 1 / 30.0f},
	{"Cheering", 1.0f, 0.3f, 1 / 30.0f},
	{"Clapping", 1.0f, 0.3f, 1 / 30.0f}, 
	{"Excited", 1.0f, 0.3f, 1 / 30.0f}, 
	{"FistPump", 1.0f, 0.3f, 1 / 30.0f},
	{"Pain", 1.0f, 0.3f, 1 / 30.0f},
	{"Waving", 1.0f, 0.3f, 1 / 30.0f},
	{"Yeah", 1.0f, 0.3f, 1 / 30.0f},
	{"ShakeFist", 1.0f, 0.3f, 1 / 30.0f},
	{"Salute", 1.0f, 0.3f, 1 / 30.0f},
	{"WaveHand", 1.0f, 0.3f, 1 / 30.0f},
	{"Defeat", 1.0f, 0.3f, 1 / 30.0f},
	{"Surprised", 1.0f, 0.3f, 1 / 30.0f},
	{"TalkingTypeA", 1.0f, 0.3f, 1 / 30.0f},
	{"TalkingTypeB", 1.0f, 0.3f, 1 / 30.0f},
	{"SecretTalk", 1.0f, 0.3f, 1 / 30.0f},
	{"FightingIdle", 1.0f, 0.3f, 1 / 30.0f},
	{"Rush", 5.0f, 0.3f, 1 / 30.0f},
	{"Flying", 1.0f, 0.3f, 1 / 30.0f},
};

const char* GuideActor::FileName = "data/MODEL/Robot.X";

//=====================================
// コンストラクタ
//=====================================
GuideActor::GuideActor() :
	auraEmitter(nullptr),
	punchEmitter(nullptr)
{
	transform->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 15.0f));
	transform->SetScale(Vector3::One * 0.3f);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// アニメーションの作成
	anim = new AnimationManager();
	anim->LoadXFile(FileName, "Guide");

	// アニメーションセットの作成
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[AnimState(i)].tag, i, data[AnimState(i)].shiftTime);
		anim->SetPlaySpeed(i, data[AnimState(i)].playSpeed);
		anim->SetDeltaTime(i, data[AnimState(i)].deltaTime);
	}

	// アニメーション遷移のセット
	for (int i = 0; i < AnimMax; i++)
	{
		// パンチ連打とファイティングポーズだけはずっと続ける
		if (i == Rush || i == FightingIdle)
		{
			anim->SetFinishTransition(AnimState(i), AnimState(i));
		}
		//YeahとDefeatも続ける
		else if (i == Yeah || i == Defeat)
		{
			anim->SetFinishTransition(AnimState(i), AnimState(i));
		}
		// とりあえず全部アニメーション終了したらアイドルに戻す
		else
		{
			anim->SetFinishTransition(AnimState(i), AnimState(0));
		}
	}
}

//=====================================
// デストラクタ
//=====================================
GuideActor::~GuideActor()
{
	//animのデストラクタは不要
	SAFE_DELETE(anim);

	if (auraEmitter != nullptr)
		auraEmitter->SetActive(false);
}

//=====================================
// 更新
//=====================================
void GuideActor::Update()
{
	anim->Update();

	if (auraEmitter != nullptr)
		auraEmitter->SetPosition(transform->GetPosition());
	Debug();
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
// 指定の位置に向かせる
//=====================================
void GuideActor::LookAt(const D3DXVECTOR3 & pos)
{
	transform->LookAt(pos);
	transform->Rotate(180.0f, transform->Up());
}

//=====================================
// アニメーション切り替え
//=====================================
void GuideActor::ChangeAnim(AnimState next)
{
	anim->ChangeAnim((UINT)next, true);
}

//=====================================
// 移動処理
//=====================================
void GuideActor::Move(const D3DXVECTOR3 & target, int duration)
{
		auraEmitter = GameParticleManager::Instance()->SetAuraEffect(
		transform->GetPosition(),
		transform->GetPosition() - target);

	Tween::Move(*this, target, duration, EaseType::OutCubic, [&]()
	{
		auraEmitter->SetActive(false);
		auraEmitter = nullptr;
	});
}

//=====================================
// パンチスタート
//=====================================
void GuideActor::StartPunsh()
{
	ChangeAnim(AnimState::Rush);

	Transform emitterTransform = *transform;
	emitterTransform.Move(transform->Up() * 3.0f + transform->Forward() * -0.5f);
	emitterTransform.SetScale(Vector3::One);

	punchEmitter = GameParticleManager::Instance()->Generate(GameParticle::PunchEffect, emitterTransform);
}

//=====================================
// パンチ終了
//=====================================
void GuideActor::EndPunch(bool result)
{
	AnimState next = result ? AnimState::Yeah : AnimState::Defeat;
	ChangeAnim(next);

	if (punchEmitter != nullptr)
		punchEmitter->SetActive(false);
}

//=====================================
// デバッグ
//=====================================
void GuideActor::Debug()
{
	Debug::Begin("GuideActorAnimation");

	if (Debug::Button("Cheering"))
	{
		anim->ChangeAnim(Cheering);
	}
	if (Debug::Button("Clapping"))
	{
		anim->ChangeAnim(Clapping);
	}
	if (Debug::Button("Excited"))
	{
		anim->ChangeAnim(Excited);
	}
	if (Debug::Button("FistPump"))
	{
		anim->ChangeAnim(FistPump);
	}
	if (Debug::Button("Pain"))
	{
		anim->ChangeAnim(Pain);
	}
	if (Debug::Button("Waving"))
	{
		anim->ChangeAnim(Waving);
	}
	if (Debug::Button("Yeah"))
	{
		anim->ChangeAnim(Yeah);
	}
	if (Debug::Button("ShakeFist"))
	{
		anim->ChangeAnim(ShakeFist);
	}
	if (Debug::Button("Salute"))
	{
		anim->ChangeAnim(Salute);
	}
	if (Debug::Button("WaveHand"))
	{
		anim->ChangeAnim(WaveHand);
	}
	if (Debug::Button("Defeat"))
	{
		anim->ChangeAnim(Defeat);
	}
	if (Debug::Button("Surprised"))
	{
		anim->ChangeAnim(Surprised);
	}
	if (Debug::Button("TalkingTypeA"))
	{
		anim->ChangeAnim(TalkingTypeA);
	}
	if (Debug::Button("TalkingTypeB"))
	{
		anim->ChangeAnim(TalkingTypeB);
	}
	if (Debug::Button("SecretTalk"))
	{
		anim->ChangeAnim(SecretTalk);
	}
	if (Debug::Button("FightingIdle"))
	{
		anim->ChangeAnim(FightingIdle);
	}
	if (Debug::Button("Rush"))
	{
		anim->ChangeAnim(Rush);
	}
	if (Debug::Button("Flying"))
	{
		anim->ChangeAnim(Flying);
	}

	Debug::End();

}