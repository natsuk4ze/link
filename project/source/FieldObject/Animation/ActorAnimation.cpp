//=====================================
//
// アクターアニメーション[ActorAnimation.cpp]
// 機能：アクターに簡単な動きをつける
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "ActorAnimation.h"
#include "../../../Framework/Tween/Tween.h"

//=====================================
// 落下
//=====================================
void ActorAnimation::Fall(GameObject& ref, std::function<void(void)> callback)
{
	Tween::Move(ref, ref.GetPosition() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), ref.GetPosition(), 30, InQuint, callback);
}

//=====================================
// 回転しながら拡大
//=====================================
void ActorAnimation::RotateAndExpantion(GameObject& ref, std::function<void(void)> callback)
{
	Tween::Rotate(ref, ref.GetRotation() + D3DXVECTOR3(0.0f, 180.0f, 0.0f), ref.GetRotation(), 30, OutBack);
	Tween::Scale(ref, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ref.GetScale(), 30, OutBack, callback);
}

//=====================================
// 回転しながら縮小
//=====================================
void ActorAnimation::RotateAndShrink(GameObject& ref, std::function<void(void)> callback)
{
	Tween::Rotate(ref, ref.GetRotation() + D3DXVECTOR3(0.0f, 180.0f, 0.0f), ref.GetRotation(), 30, OutCirc);
	Tween::Scale(ref, ref.GetScale(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30, OutCirc, callback);
}

//=====================================
// Y軸を拡大して最終的にもとに戻る
//=====================================
void ActorAnimation::ExpantionYAndReturnToOrigin(GameObject& ref, std::function<void(void)> callback) 
{
	Tween::Scale(ref, ref.GetScale(), ref.GetScale() + D3DXVECTOR3(0.0f, 0.1f, 0.0f), 30, OutBack, [&ref, &callback] 
	{
		Tween::Scale(ref, ref.GetScale(), ref.GetScale() - D3DXVECTOR3(0.0f, 0.1f, 0.0f), 30, InOutQuint, [&callback]
		{
			callback;
		});
	});
}