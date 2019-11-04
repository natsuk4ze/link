//=====================================
//
//背景アクターコンテナ処理[BackGroundActorContainer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BackGroundActorContainer.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"
#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	コンストラクタ
	***************************************/
	BackGroundActorContainer::BackGroundActorContainer(FieldLevel level) :
		fieldLevel(level)
	{
		const unsigned ReserveSizeGround = 2500;
		const unsigned ReserveSizeRiver = 200;

		groundContainer.reserve(ReserveSizeGround);
		riverContainer.reserve(ReserveSizeRiver);
	}

	/**************************************
	デストラクタ
	***************************************/
	BackGroundActorContainer::~BackGroundActorContainer()
	{
		Utility::DeleteContainer(groundContainer);
		Utility::DeleteContainer(riverContainer);
	}

	/**************************************
	更新処理
	***************************************/
	void BackGroundActorContainer::Update()
	{
		for (auto&& ground : groundContainer)
		{
			ground->Update();
		}

		for (auto&& river : riverContainer)
		{
			river->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void BackGroundActorContainer::Draw()
	{
		for (auto&& ground : groundContainer)
		{
			ground->Draw();
		}

		for (auto&& river : riverContainer)
		{
			river->Draw();
		}
	}

	/**************************************
	読み込み処理
	***************************************/
	void BackGroundActorContainer::Load()
	{
		using Model::PlaceType;

		const char* DataName[] =
		{
			//"data/FIELD/sample01.csv",
			"data/FIELD/City/City_Field.csv",
			"data/FIELD/World/World_Field.csv",
			"data/FIELD/Space/Space_Field.csv",
		};

		//CSVファイルを読み込み
		std::ifstream stream(DataName[fieldLevel]);

		std::string line;			//CSVを1行ずつ読むバッファ
		const char Delim = ',';		//区切り文字
		int x = 0;					//PlaceのX位置
		int z = 0;					//PlaceのZ位置

		//CSVの終わりまで読み込み続ける
		while (std::getline(stream, line))
		{
			//1行分読み込んだデータを区切り文字で分割する
			std::vector<std::string> subStr;
			String::Split(subStr, line, Delim);

			x = 0;

			//分割したデータ毎にPlaceModelを作成
			for (auto&& str : subStr)
			{
				PlaceType type = Model::IntToPlaceType(std::stoi(str));
				
				D3DXVECTOR3 position = Field::FieldPosition(x, z).ConvertToWorldPosition();
				PlaceActor *actor = nullptr;

				if (type == PlaceType::River)
				{
					actor = new RiverActor(position, fieldLevel);
					riverContainer.push_back(actor);
				}
				else
				{
					//真っ平らだと不自然なので高さに少し凹凸をつける
					position.y += Math::RandomRange(-2.0f, 0.0f);

					actor = new NoneActor(position, fieldLevel);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}
	}
}