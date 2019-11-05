//=====================================
//
//WorldBackGroundContainer.cpp
//機能:Worldレベルの背景コンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "WorldBackGroundContainer.h"
#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"

#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"
#include "../../../Framework/String/String.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	コンストラクタ
	***************************************/
	WorldBackGroundContainer::WorldBackGroundContainer()
	{
		//riverContainerを海として扱う
		const unsigned ReserveSizeSea = 10000;
		const unsigned ReserveSizeGround = 2000;

		riverContainer.reserve(ReserveSizeSea);
		groundContainer.reserve(ReserveSizeGround);

		groundMesh = new InstancingMeshContainer(ReserveSizeGround);
		groundMesh->Load("data/MODEL/PlaceActor/ground.x");

		seaMesh = new InstancingMeshContainer(ReserveSizeSea);
		seaMesh->Load("data/MODEL/PlaceActor/river.x");
	}

	/**************************************
	デストラクタ
	***************************************/
	WorldBackGroundContainer::~WorldBackGroundContainer()
	{
		SAFE_DELETE(groundMesh);
		SAFE_DELETE(seaMesh);
	}

	/**************************************
	更新処理
	***************************************/
	void WorldBackGroundContainer::Update()
	{
		for (auto&& sea : riverContainer)
		{
			sea->Update();
		}
	}

	/**************************************
	描画処理
	***************************************/
	void WorldBackGroundContainer::Draw()
	{
		//地面の描画
		groundMesh->Lock();
		for (auto&& ground : groundContainer)
		{
			bool res = groundMesh->EmbedTranform(ground->GetTransform());
			if (!res)
				break;
		}
		groundMesh->Unlock();

		groundMesh->Draw();

		//海の描画
		seaMesh->Lock();
		for (auto&& sea : riverContainer)
		{
			bool res = seaMesh->EmbedTranform(sea->GetTransform());
			if (!res)
				break;
		}
		seaMesh->Unlock();

		seaMesh->Draw();
	}

	/**************************************
	読み込み処理
	***************************************/
	void WorldBackGroundContainer::Load()
	{
		using Model::PlaceType;

		//CSVファイルを読み込み
		std::ifstream layerData(Const::FieldLayerFile[0]);

		std::string layerLine;
		const char Delim = ',';		//区切り文字
		int x = 0;					//PlaceのX位置
		int z = 0;					//PlaceのZ位置

		//CSVの終わりまで読み込み続ける
		while (std::getline(layerData, layerLine))
		{
			//1行分読み込んだデータを区切り文字で分割する
			std::vector<std::string> subStrLayer;
			String::Split(subStrLayer, layerLine, Delim);

			x = 0;

			//分割したデータ毎にPlaceModelを作成
			for(auto&& layer : subStrLayer)
			{
				int type = std::stoi(layer);

				D3DXVECTOR3 position = Field::FieldPosition(x, z).ConvertToWorldPosition();
				PlaceActor *actor = nullptr;

				if (type == FieldLayer::Sea)
				{
					actor = new RiverActor(position, FieldLevel::City);		//Cityと同じなのでとりあえず
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

#ifndef _DEBUG
		//フィールドの外側の背景を作る
		//NOTE:とりあえずなので全部海にしてしまう
		const int MaxOuter = 25;
		for (int outerX = -MaxOuter; outerX < x + MaxOuter; outerX++)
		{
			for (int outerZ = -MaxOuter; outerZ < z + MaxOuter; outerZ++)
			{
				if (outerX >= 0 && outerX < x && outerZ >= 0 && outerZ < z)
					continue;

				D3DXVECTOR3 position = FieldPosition(outerX, outerZ).ConvertToWorldPosition();
				PlaceActor * actor = new RiverActor(position, FieldLevel::City);
				riverContainer.push_back(actor);
			}
		}
#endif
	}
}