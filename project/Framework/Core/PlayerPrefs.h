//=====================================
//
// PlayerPrefs.h
// 機能:データ保存機能
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERPREFS_H_
#define _PLAYERPREFS_H_

#include <string>
#include <unordered_map>
#include <fstream>

#include "../../Library/nameof/nameof.hpp"
#include "../../Library/picojson/picojson.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerPrefs
{
public:

	/*********************************************
	保存したデータの取得処理
	*********************************************/
	//bool型
	static bool GetBool(const std::string& key);

	//int型
	static int GetInt(const std::string& key);

	//float型
	static float GetFloat(const std::string& key);

	//string型
	static std::string GetString(const std::string& key);

	/*********************************************
	データの保存処理
	*********************************************/
	template<class T>
	static void Save(const std::string& key, const T& value)
	{
		std::ifstream ifs;
		ifs.open(FileName, std::ios::binary);

		if (ifs.is_open())
		{
			picojson::value val;
			ifs >> val;
			ifs.close();

			picojson::object obj = val.get<picojson::object>();
			val.get<picojson::object>()[key] = picojson::value(value);

			std::string serializeData = val.serialize();
			std::ofstream ofs;
			ofs.open(FileName, std::ios::out);
			ofs << serializeData << std::endl;
			ofs.close();
		}
		else
		{
			Initialize(key, value);
		}
	}

private:
	PlayerPrefs();
	
	//初期化処理
	template<class T>
	void Initialize(const std::string& key, T value)
	{
		picojson::object data;
		data.emplace(key, picojson::value(value));

		std::string serializeData = picojson::value(data).serialize();
		std::ofstream ofs;
		ofs.open(FileName, std::ios::out);
		ofs << serializeData << std::endl;
		ofs.close();
	}

	//JSON取得処理
	static picojson::value GetData(const std::string& key);

	static const char* FileName;
};

#endif