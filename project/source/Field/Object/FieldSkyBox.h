//=====================================
//
// FieldSkyBox.h
// 機能:フィールドスカイボックス
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDSKYBOX_H_
#define _FIELDSKYBOX_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../FieldConfig.h"

namespace Field
{
	/**************************************
	前方宣言
	***************************************/

	/**************************************
	クラス定義
	***************************************/
	class FieldSkyBox : public SkyBox
	{
	public:
		FieldSkyBox(Field::FieldLevel level);

	private:
		static const char* CityTexturePath[];
		static const char* WorldTexturePath[];
		static const char* SpaceTexturePath[];
	};
}

#endif