//=====================================
//
//数学ヘッダ[TMath.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TMATH_H_
#define _TMATH_H_

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Math
{
public:
	/**************************************
	乱数取得処理
	***************************************/
	static int RandomRange(int min, int max)
	{
		if (min == max)
			return min;

		return rand() % (max - min) + min;
	}

	static float RandomRange(float min, float max)
	{
		return (float)rand() / RAND_MAX * (max - min) + min;
	}

	/**************************************
	大小判定
	***************************************/
	template <typename T>
	static T Max(T v1, T v2)
	{
		return v1 < v2 ? v2 : v1;
	}

	template <typename T>
	static T Min(T v1, T v2)
	{
		return v1 > v2 ? v2 : v1;
	}

	/**************************************
	ラップ処理
	***************************************/
	static int WrapAround(int min, int max, int value)
	{
		int mod = (value - min) % (max - min);
		return (mod >= 0) ? mod + min : mod + max;
	}

	static float WrapAround(float min, float max, float value)
	{
		float mod = fmodf(value - min, max - min);
		return (mod >= 0.0f) ? mod + min : mod + max;
	}

	/**************************************
	クランプ
	***************************************/
	template <typename T>
	static T Clamp(T min, T max, T value)
	{
		return Max(min, Min(max, value));
	}

	/**************************************
	2次ベジェ曲線関数
	***************************************/
	template <typename T>
	static T QuadraticBezier(const T& start, const T& end, const T& c, float t)
	{
		return powf(1.0f - t, 2.0f) * start + 2 * t * (1.0f - t) * c + powf(t, 2.0f) * end;
	}

	/**************************************
	3次ベジェ曲線関数
	***************************************/
	template<typename T>
	static T CubibBezier(const T&start, const T&end, const T&c1, const T&c2, float t)
	{
		return powf(1.0f - t, 3.0f) * start
			+ 3.0f * powf(1.0f - t, 2.0f) * t * c1
			+ 3.0f * (1.0f - t) * powf(t, 2.0f) * c2
			+ powf(t, 3.0f) * end;
	}

	/**************************************
	浮動小数点比較処理
	***************************************/
	template<typename T>
	static bool Approximately(const T& a, const T& b)
	{
		return fabs(a - b) <= DBL_EPSILON * fmax(1, fmax(fabs(a), fabs(b)));
	}

private:
	Math();
};

#endif