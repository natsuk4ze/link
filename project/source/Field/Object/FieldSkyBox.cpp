//=====================================
//
//フィールドスカイボックス処理[FieldSkyBox.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldSkyBox.h"
#include "../../../Framework/Resource/ResourceManager.h"

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const char* FieldSkyBox::CityTexturePath[] = {
		"data/TEXTURE/Skybox/Epic_BlueSunset_Cam_Up.jpg",
		"data/TEXTURE/Skybox/Epic_BlueSunset_Cam_Back.jpg",
		"data/TEXTURE/Skybox/Epic_BlueSunset_Cam_Down.jpg",
		"data/TEXTURE/Skybox/Epic_BlueSunset_Cam_Front.jpg",
		"data/TEXTURE/Skybox/Epic_BlueSunset_Cam_Right.jpg",
		"data/TEXTURE/Skybox/Epic_BlueSunset_Cam_Left.jpg",
	};

	const char* FieldSkyBox::WorldTexturePath[] = {
		"data/TEXTURE/Skybox/WorldSkyBox02bUp.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bBack.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bDown.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bFront.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bLeft.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bRight.jpg",
	};

	const char* FieldSkyBox::SpaceTexturePath[] = {
		"data/TEXTURE/Skybox/SpaceUp_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceBack_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceDown_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceFront_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceRight_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceLeft_Tex.jpg",
	};

	/**************************************
	コンストラクタ
	***************************************/
	FieldSkyBox::FieldSkyBox(Field::FieldLevel level) :
		SkyBox({ 20000.0f, 20000.0f, 20000.0f })
	{
		//テクスチャ読み込み
		switch (level)
		{
		case FieldLevel::City:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(CityTexturePath[i], (Surface)i);
			}
			break;

		case FieldLevel::World:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(WorldTexturePath[i], (Surface)i);
			}
			break;

		case FieldLevel::Space:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(SpaceTexturePath[i], (Surface)i);
			}
			break;	
		}
	}

	/**************************************
	リソース読み込み処理
	***************************************/
	void FieldSkyBox::LoadResource()
	{
		for (int i = 0; i < Surface::Max; i++)
		{
			ResourceManager::Instance()->LoadTexture(CityTexturePath[i]);
			ResourceManager::Instance()->LoadTexture(WorldTexturePath[i]);
			ResourceManager::Instance()->LoadTexture(SpaceTexturePath[i]);
		}
	}
}