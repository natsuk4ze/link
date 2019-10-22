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
	static void FallAndExpantion(GameObject& ref, std::function<void(void)> callback = nullptr);				// 落下しながら拡大
	static void RotateAndExpantion(GameObject& ref, std::function<void(void)> callback = nullptr);	// 回転しながら拡大
	static void RotateAndShrink(GameObject& ref, std::function<void(void)> callback = nullptr);		// 回転しながら縮小
	static void Shrink(GameObject& ref, std::function<void(void)> callback = nullptr);				// 縮小
	static void ExpantionYAndReturnToOrigin(GameObject& ref, std::function<void(void)> callback = nullptr);	// Y軸を拡大して最終的にもとに戻る
};

#endif
