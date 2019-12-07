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
#include "SpaceGrid.h"

#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../../../Framework/Tool/DebugWindow.h"

#include "../../Effect/SpaceParticleManager.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	staticメンバ
	***************************************/
	const char* SpaceBackGroundContainer::SkyboxTexName[6] =
	{
		"data/TEXTURE/skybox/SpaceTear/Up_1K_TEX.jpg",
		"data/TEXTURE/skybox/SpaceTear/Back_1K_TEX.jpg",
		"data/TEXTURE/skybox/SpaceTear/Down_1K_TEX.jpg",
		"data/TEXTURE/skybox/SpaceTear/Front_1K_TEX.jpg",
		"data/TEXTURE/skybox/SpaceTear/Right_1K_TEX.jpg",
		"data/TEXTURE/skybox/SpaceTear/Left_1K_TEX.jpg",
	};

	/**************************************
	コンストラクタ
	***************************************/
	SpaceBackGroundContainer::SpaceBackGroundContainer()
	{
		//NoneActorは表示しないのでRiverだけリザーブする
		const unsigned ReserveTearSize = 2500;
		riverContainer.reserve(ReserveTearSize);

		tearMesh = new InstancingMeshContainer(ReserveTearSize);
		ResourceManager::Instance()->GetMesh("River-Space", tearMesh);
		tearMesh->Init();

		skybox = new SkyBox({ 20000.0f, 20000.0f, 20000.0f });
		for (int i = 0; i < SkyBox::Surface::Max; i++)
		{
			skybox->LoadTexture(SkyboxTexName[i], SkyBox::Surface(i));
		}

		grid = new SpaceGrid();
	}

	/**************************************
	デストラクタ
	***************************************/
	SpaceBackGroundContainer::~SpaceBackGroundContainer()
	{
		Utility::DeleteContainer(riverContainer);
		SAFE_DELETE(tearMesh);
		SAFE_DELETE(skybox);
		SAFE_DELETE(grid);
	}

	/**************************************
	更新処理
	***************************************/
	void SpaceBackGroundContainer::Update()
	{
		grid->Update();

		D3DXVECTOR3 rotation = skybox->GetRotation();
		rotation += Vector3::One * 0.05f;
		skybox->SetRotatition(rotation);
	}

	/**************************************
	描画処理
	***************************************/
	void SpaceBackGroundContainer::Draw()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//ステンシルでマスクを作成
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		pDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 0.0f, 0);

		tearMesh->Lock();
		for (auto&& tear : riverContainer)
		{
			bool res = tearMesh->EmbedTranform(tear->GetTransform());

			if (!res)
				break;
		}
		tearMesh->Unlock();

		tearMesh->Draw();

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		pDevice->SetRenderState(D3DRS_STENCILREF, 1);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
			D3DCOLORWRITEENABLE_RED |
			D3DCOLORWRITEENABLE_GREEN |
			D3DCOLORWRITEENABLE_BLUE |
			D3DCOLORWRITEENABLE_ALPHA);


		//裂け目を描画
		skybox->Draw();

		pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

		//グリッドのフィールドを描画
		grid->Draw();
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
					actor = new RiverActor();
					actor->Init(position, FieldLevel::Space);
					actor->Rotate(Math::RandomRange(0, 4) * 90.0f);
					riverContainer.push_back(actor);

					//パーティクルのエミッタをセット
					//D3DXVECTOR3 position = FieldPosition(x, z).ConvertToWorldPosition();
					//position.y -= 2.5f;
					//SpaceParticleManager::Instance()->Generate(SpaceParticle::SpaceTear, position);
				}
				x++;
			}

			z++;
		}

	}

	/**************************************
	海判定
	***************************************/
	bool SpaceBackGroundContainer::EnableAtlantis(const FieldPosition& position) const
	{
		//海は存在しないので無条件でfalse
		return false;
	}
}