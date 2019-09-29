//=====================================
//
//トゥイーンヘッダ[Transformween.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TWEEN_H_
#define _TWEEN_H_

#include "../../main.h"
#include "../Math/Easing.h"
#include "../Core/Transform.h"

#include <list>
#include <memory>
#include <iterator>

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/

class Tween
{
	friend class BaseGame;
public:
	static void Move(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type);
	static void Move(GameObject& ref, const D3DXVECTOR3& end, int duratino, EaseType type);

	static void Scale(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type);
	static void Scale(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type);

	static void Rotate(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type);
	static void Rotate(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type);

private:
	void Update();
	void ClearContainer();

	class Tweener;
	std::list<Tween::Tweener*> tweenerContainer;

	static Tween* mInstance;
	Tween();
	~Tween();

	class Tweener
	{
	public:
		Tweener(std::shared_ptr<Transform>& ref, int duration, EaseType type);
		virtual ~Tweener();
		inline bool IsFinished();
		virtual void Update() = 0;

	protected:
		std::weak_ptr<Transform> reference;
		int cntFrame;
		int duration;
		EaseType type;
	};

	class MoveTweener : public Tweener
	{
	public:
		MoveTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type);
		void Update();
		
	private:
		D3DXVECTOR3 start, end;
	};

	class ScaleTweener : public Tweener
	{
	public:
		ScaleTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type);
		void Update();

	private:
		D3DXVECTOR3 start, end;
	};

	class RotateTweener : public Tweener
	{
	public:
		RotateTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type);
		void Update();

	private:
		D3DXQUATERNION start, end;
	};
};

#endif