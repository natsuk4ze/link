//=====================================
//
// アクターアニメーション[ActorAnimation.h]
// 機能：アクターに簡単な動きをつける
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _ACTORANIMATION_H_
#define _ACTORANIMATION_H_

#include <functional>
#include "../../../Framework/Core/GameObject.h"
//**************************************
// クラス定義
//**************************************
class ActorAnimation
{
	friend class Tween;
public:
	static void Fall(GameObject& ref, std::function<void(void)> callback = nullptr);
	static void RotateAndExpantion(GameObject& ref, std::function<void(void)> callback = nullptr);
	static void RotateAndShrink(GameObject& ref, std::function<void(void)> callback = nullptr);

};

#endif
