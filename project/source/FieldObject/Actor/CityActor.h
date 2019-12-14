//=====================================
//
// シティアクター[CityActor.cpp]
// 機能：都市（国、星）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _CITYACTOR_H_
#define _CITYACTOR_H_

#include "PlaceActor.h"
//**************************************
// 前方宣言
//**************************************
class MorphingMeshContainer;

//**************************************
// クラス定義
//**************************************
class CityActor :
	public PlaceActor
{
public:
	CityActor();
	~CityActor();

	void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void StartMorph(int next);

	static const int DurationMorphing;

private:
	MorphingMeshContainer * morphContainer;		//モーフィング用メッシュコンテナ
	
	bool useMorphing;							//モーフィングを使用するかどうか
	bool inMorphing;							//モーフィング中かどうか

	int cntFrameMorphing;						//モーフィング中のカウンタ
	int currentMorphing;						//現在のモーフィングインデックス
};

#endif
