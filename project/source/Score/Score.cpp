//=====================================
//
// スコア[Score.cpp]
// 機能：スコア管理クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "Score.h"

namespace Field
{
	//=====================================
	// コンストラクタ
	//=====================================
	Score::Score() :
		developmentLevelAI(0),
		current(FieldLevel::City)
	{
	}


	//=====================================
	// デストラクタ
	//=====================================
	Score::~Score()
	{
	}

	//=====================================
	// スコアの取得
	//=====================================
	UINT Score::GetScore()
	{
		return developmentLevelAI;
	}

	//=====================================
	// スコアの加算
	//=====================================
	void Score::AddScore(UINT score, FieldLevel current)
	{
		this->current = current;
		switch (this->current)
		{
		case Field::City:
			developmentLevelAI += score;
			break;
		case Field::World:
			developmentLevelAI += score * 10000 + 9999;
			break;
		case Field::Space:
			developmentLevelAI += score * 100000000 + 99999999;
			break;
		}
	}
}
