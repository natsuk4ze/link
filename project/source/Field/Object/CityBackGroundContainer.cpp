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
#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"
#include "../../../Framework/Core/ObjectPool.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	コンストラクタ
	***************************************/
	CityBackGroundContainer::CityBackGroundContainer()
	{
		const unsigned ReserveSizeGround = 10000;
		const unsigned ReserveSizeRiver = 200;

		groundContainer.reserve(ReserveSizeGround);
		riverContainer.reserve(ReserveSizeRiver);

		groundMesh = new InstancingMeshContainer(ReserveSizeGround);
		groundMesh->Load("data/MODEL/PlaceActor/ground.x");
	}

	/**************************************
	デストラクタ
	***************************************/
	CityBackGroundContainer::~CityBackGroundContainer()
	{
		SAFE_DELETE(groundMesh);
	}

	/**************************************
	更新処理
	***************************************/
	void CityBackGroundContainer::Update()
	{
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
		//地面はインスタンシングで描画する
		groundMesh->Lock();
		for (auto&& ground : groundContainer)
		{
			bool result = groundMesh->EmbedTranform(ground->GetTransform());
			if (!result)
				break;
		}
		groundMesh->Unlock();

		groundMesh->Draw();

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

		//川の流れる方向のデータを読み込み
		std::map<FieldPosition, int> flowMap = LoadRiverFlowData();

		//CSVファイルを読み込み
		std::ifstream stream(Const::FieldDataFile[0]);

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

				FieldPosition position = Field::FieldPosition(x, z);

				if (type == PlaceType::River)
				{
					RiverActor *actor = ObjectPool::Instance()->Create<RiverActor>(position.ConvertToWorldPosition(), FieldLevel::City);
					riverContainer.push_back(actor);

					actor->SetDirection((RiverActor::FlowDirection)flowMap[position]);
				}
				else
				{
					//真っ平らだと不自然なので高さに少し凹凸をつける
					D3DXVECTOR3 offset = { 0.0f, Math::RandomRange(-2.0f, 0.0f), 0.0f };

					NoneActor *actor = ObjectPool::Instance()->Create<NoneActor>(position.ConvertToWorldPosition() + offset, FieldLevel::City);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}

#ifndef _DEBUG
		//フィールドの外側の背景を作る
		//NOTE:とりあえずなので全部地面にしてしまう
		const int MaxOuter = 25;
		for (int outerX = -MaxOuter; outerX < x + MaxOuter; outerX++)
		{
			for (int outerZ = -MaxOuter; outerZ < z + MaxOuter; outerZ++)
			{
				if (outerX >= 0 && outerX < x && outerZ >= 0 && outerZ < z)
					continue;

				D3DXVECTOR3 position = FieldPosition(outerX, outerZ).ConvertToWorldPosition();
				position.y += Math::RandomRange(-2.0f, 0.0f);
				PlaceActor* actor = ObjectPool::Instance()->Create<NoneActor>(position, FieldLevel::City);
				groundContainer.push_back(actor);
			}
		}
#endif
	}

	/**************************************
	海判定
	***************************************/
	bool CityBackGroundContainer::EnableAtlantis(const FieldPosition& position) const
	{
		//海は存在しないので無条件でfalse
		return false;
	}

	/**************************************
	川データ読み込み
	***************************************/
	std::map<FieldPosition, int> CityBackGroundContainer::LoadRiverFlowData()
	{
		std::map<FieldPosition, int> out;

		//CSVファイルを読み込み
		std::ifstream stream(Const::RiverFlowFile[0]);

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
				int flowDir = std::stoi(str);

				if (flowDir != -1)
				{
					FieldPosition position = Field::FieldPosition(x, z);
					out.emplace(position, flowDir);
				}
				x++;
			}

			z++;
		}

		return out;
	}
}