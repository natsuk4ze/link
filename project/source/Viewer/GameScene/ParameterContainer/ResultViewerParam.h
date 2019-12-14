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
	int score[fieldTypeMax] = { 0,0,0 };

	//Cityで作った道の数,Worldで作った道の数、Spaceで作った道の数
	int builtRoad[fieldTypeMax] = { 0,0,0 };

	//Cityで繋がった街の数,Worldで繋がった街の数、Spaceで繋がった街の数
	int connectedCity[fieldTypeMax] = { 0,0,0 };

	// パラメータをクリアする
	void Clear(void)
	{
		for (int i = 0; i < fieldTypeMax; i++)
		{
			score[i] = 0;
			builtRoad[i] = 0;
			connectedCity[i] = 0;
		}
	}
};

#endif