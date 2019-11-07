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
#include "FieldErrorMessage.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class FieldTelop;
class FieldErrorMessage;
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

	//フィールドテロップをセット（お試しで実装中）
	void SetFieldTelop(FieldTelop::TelopID id, std::function<void(void)> Callback);

	//フィールドエラーメッセージをセット
	void SetFieldErroMessage(FieldErrorMessage::ErroID id);

	std::vector <BaseViewer*> fieldViewer;

private:
	FieldTelop * fieldTelop;
	FieldErrorMessage * fieldErroMessage;
};

#endif

