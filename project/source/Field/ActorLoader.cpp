//=====================================
//
//アクターローダー処理[ActorLoader.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ActorLoader.h"
#include "../../Library/json11/json11.hpp"
#include "../Field/FieldConfig.h"
#include "../../Framework/Resource/ResourceManager.h"

#include <string>
#include <fstream>

namespace Field::Actor
{
	/**************************************
	タウンモデルのタグ
	***************************************/
	const std::string ActorLoader::CityTag[] = {
		"City-Town",
		"World-Town",
		"Space-Town"
	};

	/**************************************
	カーブ道のタグ
	***************************************/
	const std::string ActorLoader::StraightTag[] = {
		"City-Straight",
		"World-Straight",
		"Space-Straight"
	};

	/**************************************
	直線道のタグ
	***************************************/
	const std::string ActorLoader::CurveTag[] = {
		"City-Curve",
		"World-Curve",
		"Space-Curve",
	};

	/**************************************
	T字路のタグ
	***************************************/
	const std::string ActorLoader::TJunctionTag[] = {
		"City-T",
		"World-T",
		"Space-T"
	};

	/**************************************
	十字路のタグ
	***************************************/
	const std::string ActorLoader::CrossTag[] = {
		"City-Cross",
		"World-Cross",
		"Space-Cross"
	};

	/**************************************
	橋のタグ
	**************************************/
	const std::string ActorLoader::BridgeTag[] = {
		"City-Bridge",
		"World-Bridge",
		"Space-Bridge"
	};

	/**************************************
	山のタグ
	***************************************/
	const std::string ActorLoader::MountainTag[] = {
		"City-Mountain",
		"World-Mountain",
		"Space-Mountain"
	};

	/**************************************
	水上のアクターのタグ
	***************************************/
	const std::string ActorLoader::WaterStraight = "World-StraightSea";
	const std::string ActorLoader::WaterCurve = "World-CurveSea";
	const std::string ActorLoader::WaterT = "World-TSea";
	const std::string ActorLoader::WaterCross = "World-CrossSea";

	/**************************************
	渦潮のリソースタグ
	***************************************/
	const std::string ActorLoader::WhirlPoolTag = "World-WhirlPool";

	/**************************************
	地面のリソースタグ
	***************************************/
	const std::string ActorLoader::GroundTag = "Ground";

	/**************************************
	川のリソースタグ
	***************************************/
	const std::string ActorLoader::RiverTag = "River";

	/**************************************
	町レベルの町モデルリソースタグ
	***************************************/
	const std::string ActorLoader::CityTownTag[3] =
	{
		"City-Town-S",
		"City-Town-M",
		"City-Town-L"
	};

	/**************************************
	世界レベルの町モデルリソースタグ
	***************************************/
	const std::string ActorLoader::WorldTownTag[3] =
	{
		"World-Town-S",
		"World-Town-M",
		"World-Town-L"
	};

	/**************************************
	コンストラクタ
	***************************************/
	ActorLoader::ActorLoader()
	{

	}

	/**************************************
	デストラクタ
	***************************************/
	ActorLoader::~ActorLoader()
	{
		modelFileName.clear();
	}

	/**************************************
	設定ファイルの読み込み	
	***************************************/
	void ActorLoader::LoadConfig()
	{
		//設定ファイルを開く
		std::string filePath = "data/PlaceActorConfig.txt";
		std::ifstream ifs;
		ifs.open(filePath, std::ios::in);

		//成功確認
		assert(ifs.is_open());

		//JSONデータを読み込み
		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		std::string err;
		json11::Json data = json11::Json::parse(json, err);

		//データをパース
		for (int i = 0; i <= Field::FieldLevel::Space; i++)
		{
			modelFileName[CityTag[i]] = data[CityTag[i]].string_value();
			modelFileName[StraightTag[i]] = data[StraightTag[i]].string_value();
			modelFileName[CurveTag[i]] = data[CurveTag[i]].string_value();
			modelFileName[TJunctionTag[i]] = data[TJunctionTag[i]].string_value();
			modelFileName[CrossTag[i]] = data[CrossTag[i]].string_value();
			modelFileName[BridgeTag[i]] = data[BridgeTag[i]].string_value();
			modelFileName[MountainTag[i]] = data[MountainTag[i]].string_value();
		}

		modelFileName[WaterStraight] = data[WaterStraight].string_value();
		modelFileName[WaterCurve] = data[WaterCurve].string_value();
		modelFileName[WaterT] = data[WaterT].string_value();
		modelFileName[WaterCross] = data[WaterCross].string_value();
		modelFileName[WhirlPoolTag] = data[WhirlPoolTag].string_value();
		modelFileName[GroundTag] = data[GroundTag].string_value();
		modelFileName[RiverTag] = data[RiverTag].string_value();

		for (int i = 0; i < 3; i++)
		{
			modelFileName[CityTownTag[i]] = data[CityTownTag[i]].string_value();
			modelFileName[WorldTownTag[i]] = data[WorldTownTag[i]].string_value();
		}
	}

	/**************************************
	リソース読み込み
	***************************************/
	void ActorLoader::LoadResource()
	{
		//リソースを読み込み
		for (auto&& pair : modelFileName)
		{
			if (pair.second == "")
				continue;

			ResourceManager::Instance()->LoadMesh(pair.first.c_str(), pair.second.c_str());
		}
	}
}