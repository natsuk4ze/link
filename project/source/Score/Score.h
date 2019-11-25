//=====================================
//
// スコア[Score.h]
// 機能：スコア管理クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "../../main.h"
#include "../Field/FieldController.h"

//**************************************
// クラス定義
//**************************************
namespace Field
{
	class Score
	{
	private:
		FieldLevel current;	// 現在のフィールドレベル
		int score[FieldLevel::Max];	// それぞれのフィールドのスコア

	public:
		Score();
		~Score();

		int GetScore(FieldLevel level);					// スコアの取得
		void SetScore(int score, FieldLevel current);	// スコアのセット
	};
}

#endif
