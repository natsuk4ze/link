//=====================================
//
// ネーム[Name.h]
// 機能：ネームのデータを保存するクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _NAME_H_
#define _NAME_H_

//**************************************
// クラス定義
//**************************************
class Name
{
private:
	int num[3];

public:
	Name();
	Name(int first, int second, int third);
	~Name();

	// コピーコンストラクタ
	Name(const Name& in);

	void Set(int first, int second, int third);

	int Get(int No);
};

#endif
