//=====================================
//
//ベースシングルトンヘッダ[BaseSingleton.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASESINGLETON_H_
#define _BASESINGLETON_H_

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
template <class T>
class BaseSingleton
{	
public:
	static T* Instance()
	{
		static T mInstance;

		return &mInstance;
	}

protected:
	BaseSingleton() {}
	virtual ~BaseSingleton() {}

	BaseSingleton(const BaseSingleton &) = delete;
	BaseSingleton(BaseSingleton &&) = delete;

	BaseSingleton& operator=(const BaseSingleton &) = delete;
	BaseSingleton& operator=(BaseSingleton &&) = delete;
};

#endif