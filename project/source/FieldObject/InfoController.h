#ifndef _INFOCONTROLLER_H_
#define _INFOCONTROLLER_H_

#include <map>
#include "Infomation/LinkInfoActor.h"
#include "../Field/FieldConfig.h"

class InfoController
{
private:
	std::map<Field::FieldPosition, LinkInfoActor*> LinkInfoMap; // リンクレベル表示用

public:
	InfoController();
	~InfoController();

	void Update();
	void Draw();

	// 町のリンクレベルのセット、レベルアップ
	void SetLinkLevel(const Field::FieldPosition& key, const int& townLevel);
};

#endif
