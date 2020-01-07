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
	const char* Const::FieldDataFile[] = {
		"data/FIELD/City/City_Field.csv",
		"data/FIELD/World/World_Field.csv",
		"data/FIELD/Space/Space_Field.csv",
		"data/FIELD/Tutorial/Tutorial_Field.csv",
	};

	/**************************************
	陸地と海のレイヤーCSVファイル名
	***************************************/
	const char* Const::FieldLayerFile[] = {
		"data/FIELD/World/World_Continent.csv",
	};

	/**************************************
	川の流れる向きのCSVファイル名
	***************************************/
	const char* Const::RiverFlowFile[] = {
		"data/FIELD/City/City_Flow.csv",
	};
}