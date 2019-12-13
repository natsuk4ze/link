//=============================================================================
//
// 基底Viewer処理 [BaseViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BASE_VIEWER_H_
#define _BASE_VIEWER_H_

//*****************************************************************************
// 基底クラス定義
//*****************************************************************************
class BaseViewer
{
private:
	float currentParam = 0;
	float lastParam = 0;

public:
	BaseViewer() {};
	virtual ~BaseViewer() {};

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//現在フレームのパラメータと前フレームのパラメータを比較して結果を返す
	template <class T>
	bool isCurrentGreaterLast(const T param)
	{
		bool isGreater = false;

		currentParam = param;
		if (currentParam > lastParam)
		{
			isGreater = true;
		}
		lastParam = param;

		return isGreater;
	};

	template <class T>
	bool isCurrentSmallerLast(const T param)
	{
		bool isSmaller = false;

		currentParam = param;
		if (currentParam < lastParam)
		{
			isSmaller = true;
		}
		lastParam = param;

		return isSmaller;
	};

	template <class T>
	bool isCurrentEqualLast(const T param)
	{
		bool isEqual = false;

		currentParam = param;
		if (currentParam == lastParam)
		{
			isEqual = true;
		}
		lastParam = param;

		return isEqual;
	};

	//再生中かどうか
	bool isPlaying;
};

#endif

