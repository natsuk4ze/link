//=============================================================================
//
// リザルトビュアーパラメータ [ResultViewerParam.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_VIEWER_PARAM_H_
#define _RESULT_VIEWER_PARAM_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultViewerParam
{
public:
	const static int fieldTypeMax = 3;

	//Cityスコア,Worldスコア,Spaceスコア
	int score[fieldTypeMax];

	//Cityで達成したリワード数,Worldで達成したリワード数、Spaceで達成したリワードの数
	int completedRewardNum[fieldTypeMax];
};

#endif