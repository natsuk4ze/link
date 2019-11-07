//=====================================
//
// インフォコントローラ[InfoController.h]
// 機能：InfoActorのコントローラクラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _INFOCONTROLLER_H_
#define _INFOCONTROLLER_H_

#include <map>
#include "Infomation/LinkInfoActor.h"
#include "../Field/FieldConfig.h"
#include "../Field/Place/PlaceConfig.h"

//**************************************
// クラス定義
//**************************************
class InfoController
{
private:
	std::map<Field::FieldPosition, LinkInfoActor*> LinkInfoMap; // リンクレベル表示用

	// 町のリンクレベルのセット、レベルアップ
	void SetLinkLevel(const Field::PlaceData& data);

public:
	InfoController();
	~InfoController();

	void Update();
	void Draw();

	// 全ての町のリンクレベルのセット、レベルアップ
	void SetAllLinkLevel(const std::vector<Field::PlaceData>& vec);
};

#endif
