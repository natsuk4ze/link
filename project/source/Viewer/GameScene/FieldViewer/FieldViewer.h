//=============================================================================
//
// Fieldビュアー管理処理 [FieldViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_VIEWER_H_
#define _FIELD_VIEWER_H_

#include <vector>
#include "FieldTelop.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class FieldTelop;
class BaseViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FieldViewer
{
public:
	FieldViewer();
	~FieldViewer();

	void Update(void);
	void Draw(void);

	void SetFieldTelop(FieldTelop::TelopID id, std::function<void(void)> Callback);
	std::vector <BaseViewer*> fieldViewer;

private:
	FieldTelop * fieldTelop;
};

#endif

