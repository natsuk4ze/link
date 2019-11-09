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
#include "OperationExplanationViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class FieldTelop;
class LinkLevelUpViewer;
class FieldErrorMessage;
class OperationExplanationViewer;
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

	//操作説明ビューアをセット
	void SetOperationExplanation(
		//Zキーの操作に表示する説明ID
		OperationExplanationViewer::OperationID id0, 
		//Xキーの操作に表示する説明ID
		OperationExplanationViewer::OperationID id1, 
		//Spaceキーの操作に表示する説明ID
		OperationExplanationViewer::OperationID id2);

	//上昇した分のリンクレベルを表示する
	void ViewLinkLevelUp(int level);

private:
	std::vector <BaseViewer*> fieldViewer;

	FieldTelop * fieldTelop;
	LinkLevelUpViewer *linkLevelUpViewer;
	FieldErrorMessage * fieldErroMessage;
	OperationExplanationViewer *operationExplanation;
};

#endif

