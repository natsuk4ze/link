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
#include <functional>

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
	friend class SceneManager;
public:
	/**************************************
	移動トゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 start : 移動開始座標
	引数 end : 移動先座標
	引数 duration : 移動にかける時間
	引数 type : イージングタイプ
	引数 callback : 終了時のコールバック関数
	***************************************/
	static void Move(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	移動トゥイーン
	基本的には上記と一緒だが、移動開始座標を現在座標に自動で設定してくれる
	***************************************/
	static void Move(GameObject& ref, const D3DXVECTOR3& end, int duratino, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	スケールトゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 start : 開始時のスケール
	引数 end : 終了時のスケール
	引数 duration : スケールにかける時間
	引数 type : イージングタイプ
	引数 callback : 終了時のコールバック関数
	***************************************/
	static void Scale(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	スケールトゥイーン
	基本的には上記と一緒だが開始時のスケールを現在スケールに自動で設定してくれる
	***************************************/
	static void Scale(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	回転トゥイーン
	引数 ref：トゥイーン対象のゲームオブジェクト
	引数 start : 回転開始角度（オイラー角）
	引数 end : 回転終了角度（オイラー角）
	引数 duration : 回転にかける時間
	引数 type : イージングタイプ
	引数 callback : 終了時のコールバック関数
	※回転角度は自動で0.0f~360.0fに補正されてしまうので注意
	***************************************/
	static void Rotate(GameObject& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback = nullptr);

	/**************************************
	回転トゥイーン
	基本的には上記と一緒だが開始の回転角度を自動で現在角度に設定してくれる
	***************************************/
	static void Rotate(GameObject& ref, const D3DXVECTOR3& end, int duration, EaseType type, std::function<void(void)> callback = nullptr);

private:
	void Update();
	void ClearContainer();
	void ClearAll();

	class Tweener;
	std::list<Tween::Tweener*> tweenerContainer;

	static Tween* mInstance;
	Tween();
	~Tween();

	using Callback = std::function<void(void)>;

	class Tweener
	{
	public:
		Tweener(std::shared_ptr<Transform>& ref, int duration, EaseType type, Callback callback);
		virtual ~Tweener();
		inline bool IsFinished();
		virtual void Update() = 0;
		inline void CheckCallback();

	protected:
		std::weak_ptr<Transform> reference;
		int cntFrame;
		int duration;
		EaseType type;
		Callback callback;
	};

	class MoveTweener : public Tweener
	{
	public:
		MoveTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback);
		void Update();

	private:
		D3DXVECTOR3 start, end;
	};

	class ScaleTweener : public Tweener
	{
	public:
		ScaleTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback);
		void Update();

	private:
		D3DXVECTOR3 start, end;
	};

	class RotateTweener : public Tweener
	{
	public:
		RotateTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback);
		void Update();

	private:
		D3DXQUATERNION start, end;
	};
};

#endif