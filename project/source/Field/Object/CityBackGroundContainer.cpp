//=====================================
//
//背景アクターコンテナ処理[CityBackGroundContainer.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "CityBackGroundContainer.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"

#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************コンストラクタ
	***************************************/
	CityBackGroundContainer::CityBackGroundContainer()
	{
		const unsigned ReserveSizeGround = 2500;
		const unsigned ReserveSizeRiver = 200;

		groundContainer.reserve(ReserveSizeGround);
		riverContainer.reserve(ReserveSizeRiver);
	}

	/**************************************
	デストラクタ
	***************************************/
	CityBackGroundContainer::~CityBackGroundContainer()
	{
		Utility::DeleteContainer(groundContainer);
		Utility::DeleteContainer(riverContainer);
	}

	/**************************************
	更新処理
	***************************************/
	void CityBackGroundContainer::Update()
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
	void CityBackGroundContainer::Draw()
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
	void CityBackGroundContainer::Load()
	{
		using Model::PlaceType;

		const char* DataName = "data/FIELD/City/City_Field.csv";

		//CSVファイルを読み込み
		std::ifstream stream(DataName);

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
					actor = new RiverActor(position, FieldLevel::City);
					riverContainer.push_back(actor);
				}
				else
				{
					//真っ平らだと不自然なので高さに少し凹凸をつける
					position.y += Math::RandomRange(-2.0f, 0.0f);

					actor = new NoneActor(position, FieldLevel::City);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}

		//フィールドの外側の背景を作る
		//NOTE:とりあえずなので全部地面にしてしまう
		const int MaxOuter = 50;
		for (int outerX = -MaxOuter; outerX < x + MaxOuter; outerX++)
		{
			for (int outerZ = -MaxOuter; outerZ < z + MaxOuter; outerZ++)
			{
				if (outerX >= 0 && outerX < x && outerZ >= 0 && outerZ < z)
					continue;

				D3DXVECTOR3 position = FieldPosition(outerX, outerZ).ConvertToWorldPosition();
				position.y += Math::RandomRange(-2.0f, 0.0f);
				PlaceActor * actor = new NoneActor(position, FieldLevel::City);
				groundContainer.push_back(actor);
			}
		}
	}
}