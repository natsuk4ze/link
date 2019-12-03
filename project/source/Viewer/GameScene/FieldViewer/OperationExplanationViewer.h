//=============================================================================
//
// 操作説明ビューア処理 [OperationExplanationViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _OPERATION_EXPLANATION_VIEWER_H_
#define _OPERATION_EXPLANATION_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class OperationExplanationViewer :public BaseViewer
{
public:
	OperationExplanationViewer();
	~OperationExplanationViewer();

	//オペレーションの種類
	enum OperationID
	{
		//Zについて「道を作る」を表示する
		Z_Build,
		//Zについて「キャンセル」を表示する
		Z_Cancel,
		//Xについて「開拓する」を表示する
		X_Develop,
		//Xについて「キャンセル」を表示する
		X_Cancel,
		//Spaceについて「視点変更」を表示する
		Space_Change,
		//Zについての操作を表示しない
		Z_None,
		//Xについての操作を表示しない
		X_None,
		//Spaceについての操作を表示しない
		Space_None,
		//種類数
		Max
	};

	void Update();
	void Draw(void);
	void Set(OperationID id0, OperationID id1, OperationID id2);

private:

	const static int textMax = 3;

	//テキスト
	BaseViewerDrawer * text[textMax];

	//テクスチャUVセット処理
	void SetTexture(OperationID id0, OperationID id1, OperationID id2);
};

#endif