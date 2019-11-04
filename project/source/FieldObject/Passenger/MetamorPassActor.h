//=====================================
//
// メタモルパスアクター[MetamorPassActor.h]
// 機能：フィールド上を行き来するアクター（国レベルで使用。モデルが動的に切り替わる）
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _METAMORPASSACTOR_H_
#define _METAMORPASSACTOR_H_

#include "PassengerActor.h"

//**************************************
// クラス定義
//**************************************
class MetamorPassActor :
	public PassengerActor
{
private:
	Field::FieldPosition fieldPos;	// フィールド上の座標

	// メッシュの状態を表すステート
	enum State
	{
		Ship,
		Train,
	};
	State current;					// 現在のメッシュの状態
	bool change;					// メッシュ切り替えフラグ

	void CheckState();

public:
	MetamorPassActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~MetamorPassActor();

	void Update()override;

	Field::FieldPosition FieldPosition();	// フィールド上の座標を返す
	void SetChange(bool flag);				// 　メッシュ切り替えフラグのセット
};

#endif
