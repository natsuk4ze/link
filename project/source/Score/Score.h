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
		UINT developmentLevelAI;	// 総AI発展レベル＝スコア

	public:
		Score();
		~Score();

		UINT GetScore();			// スコアの取得
		void AddScore(UINT score, FieldLevel current);	// スコアの加算
	};
}

#endif
