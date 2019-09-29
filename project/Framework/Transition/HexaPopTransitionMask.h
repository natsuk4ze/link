//=====================================
//
//ヘキサポップトランジションヘッダ[HexaTransitionMaskPop.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _HEXAPOPTRANSITIONMASK_H_
#define _HEXAPOPTRANSITIONMASK_H_

#include "../../main.h"
#include "BaseTransitionMask.h"
#include "../Math/Easing.h"

#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class HexaPopTransitionMask : public BaseTransitionMask
{
public:
	//コンストラクタ、デストラクタ
	HexaPopTransitionMask();
	~HexaPopTransitionMask();

	MaskResult Update() override;				//更新処理
	void Draw() override;						//描画処理
	void Set(bool isTransitionOut) override;	//セット処理

private:
	//マスク領域となる六角形のインナークラス
	class Hexagon
	{
	public:
		Hexagon(D3DXVECTOR3 pos);

		void Init();
		void Update(HexaPopTransitionMask& parent);
		bool IsLastHexa(HexaPopTransitionMask& parent);

		Transform transform;
		int cntFrame;
		bool active;
	};

	//カウンタ
	int cntFrame;
	UINT rowIndex;

	//六角形のベクターとイテレータ
	std::vector<std::vector<Hexagon*>> hexList;
	std::vector<std::vector<Hexagon*>::iterator> itrList;

	//イージングパラメータ
	D3DXVECTOR3 startScale, endScale;
	EaseType type;

	//終了フラグ
	bool isFinished;

	//ポリゴン
	Polygon2D *polygon;
};

#endif