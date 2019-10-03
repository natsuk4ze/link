//=====================================
//
//Template.cpp
//機能:文字列操作
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "String.h"

/**************************************
文字列分割処理
***************************************/
void String::Split(std::vector<std::string>& out, std::string & str, const char delim)
{
	unsigned first = 0;							//始点
	unsigned last = str.find_first_of(delim);	//終点

	while (first < str.size())
	{
		//カンマの位置までの文字列を切り出す
		std::string subStr(str, first, last - first);

		out.push_back(subStr);

		//次にカンマが現れるとこまで始点と終点を更新
		first = last + 1;
		last = str.find_first_of(delim, first);

		if (last == std::string::npos)
		{
			last = str.size();
		}

	}
}
