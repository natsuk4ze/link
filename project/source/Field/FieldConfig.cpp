//=====================================
//
//フィールドコンフィグ処理[FieldConfig.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldConfig.h"

namespace Field
{
	/**************************************
	フィールドのCSVファイル名
	***************************************/
	const char* Const::CityDataFile[] = {
		"data/FIELD/City/City_Field.csv",
		"data/FIELD/City/City1_Field.csv",
		"data/FIELD/City/City2_Field.csv",
	};
	const char* Const::WorldDataFile[] = {
		"data/FIELD/World/World_Field.csv",
		"data/FIELD/World/World1_Field.csv",
		"data/FIELD/World/World2_Field.csv",
	};
	const char* Const::SpaceDataFile[] = {
		"data/FIELD/Space/Space_Field.csv",
		"data/FIELD/Space/Space1_Field.csv",
		"data/FIELD/Space/Space2_Field.csv",
	};
	const char* Const::TutorialDataFile = "data/FIELD/Tutorial/Tutorial_Field.csv";

	/**************************************
	陸地と海のレイヤーCSVファイル名
	***************************************/
	const char* Const::FieldLayerFile[] = {
		"data/FIELD/World/World_Continent.csv",
		"data/FIELD/World/World1_Continent.csv",
		"data/FIELD/World/World2_Continent.csv"
	};

	/**************************************
	川の流れる向きのCSVファイル名
	***************************************/
	const char* Const::RiverFlowFile[] = {
		"data/FIELD/City/City_Flow.csv",
		"data/FIELD/City/City1_Flow.csv",
		"data/FIELD/City/City2_Flow.csv"
	};
}