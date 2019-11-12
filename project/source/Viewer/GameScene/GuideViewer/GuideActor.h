//=====================================
//
// ガイドアクター[GuideViewer.h]
// 機能：ガイド役キャラクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _GUIDEACTOR_H_
#define _GUIDEACTOR_H_

#include "../../../../Framework/Core/GameObject.h"
#include "../../../../Framework/Animation/AnimationManager.h"

//**************************************
// クラス定義
//**************************************
class GuideActor :
	public GameObject
{
public:
	// アニメーションステート
	enum AnimState
	{
		Idle,
		Running,
		AnimMax
	};

	// アニメーション読み込みデータ用構造体
	struct AnimData
	{
		const char* tag;
		float playSpeed;
		float shiftTime;
		float deltaTime;
	};

	GuideActor();
	~GuideActor();

	void Update();
	void Draw();

	void ChangeAnim(AnimState next);

private:
	AnimationManager* anim;					// アニメーションマネージャ
	static const AnimData data[AnimMax];	// アニメーション読み込み用データ
};

#endif

