//=====================================
//
//SpaceBackGroundContainer.cpp
//機能:宇宙レベルの背景コンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SpaceBackGroundContainer.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"

#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"

#include "../../Effect/GameParticleManager.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	コンストラクタ
	***************************************/
	SpaceBackGroundContainer::SpaceBackGroundContainer()
	{
		//NoneActorは表示しないのでRiverだけリザーブする
		const unsigned ReserveTearSize = 1000;

		//riverContainer.reserve(ReserveTearSize);

		//tearMesh = new InstancingMeshContainer(ReserveTearSize);
		//tearMesh->Load("data/MODEL/PlaceActor/SpaceTear.x");
	}

	/**************************************
	デストラクタ
	***************************************/
	SpaceBackGroundContainer::~SpaceBackGroundContainer()
	{
		//Utility::DeleteContainer(riverContainer);
	}

	/**************************************
	更新処理
	***************************************/
	void SpaceBackGroundContainer::Update()
	{
	}

	/**************************************
	描画処理
	TODO:半透明オブジェクトが含まれるので制御する
	***************************************/
	void SpaceBackGroundContainer::Draw()
	{
		//LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		//tearMesh->Lock();
		//for (auto&& tear : riverContainer)
		//{
		//	tearMesh->EmbedTranform(tear->GetTransform());
		//}
		//tearMesh->Unlock();

		//tearMesh->Draw();

		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}

	/**************************************
	読み込み処理
	***************************************/
	void SpaceBackGroundContainer::Load()
	{
		using Model::PlaceType;

		//CSVファイルを読み込み
		std::ifstream stream(Const::FieldDataFile[FieldLevel::Space]);

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
					//actor = new RiverActor(position, FieldLevel::Space);
					//riverContainer.push_back(actor);

					//パーティクルのエミッタをセット
					D3DXVECTOR3 position = FieldPosition(x, z).ConvertToWorldPosition();
					GameParticleManager::Instance()->Generate(GameParticle::SpaceTear, position);
				}
				x++;
			}

			z++;
		}
	}
}