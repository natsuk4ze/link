//=====================================
//
// 板ポリゴン描画クラス[PolygonDrawer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _PolygonDrawer_H_
#define _PolygonDrawer_H_

#include "../../../../Framework/Renderer3D/BoardPolygon.h"

enum MovePolygonType
{
	Wall,
	Ground,
	Max
};


/**************************************
クラス定義
***************************************/
class PolygonDrawer : public BoardPolygon
{
private:
	D3DXVECTOR3 Pos;		// 板ポリゴンの現在座標
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 DestPos;	// 移動の目標座標
	D3DXVECTOR3 StartPos;	// 初期座標
	bool Movable;			// 移動フラグ
	float MoveSpeed;

	void SetPolygonPara(const char* Tag, int Num);

public:
	//コンストラクタ、デストラクタ
	PolygonDrawer(const char* Tag, D3DXVECTOR3 Pos);
	PolygonDrawer(const char* Tag, D3DXVECTOR3 StartPos, D3DXVECTOR3 DestPos);
	PolygonDrawer(const char* Tag, D3DXVECTOR3 StartPos, D3DXVECTOR3 DestPos, int Num);
	~PolygonDrawer();

	// 更新処理
	void Update(void);
	// 描画処理
	void Draw(void);
	// テクスチャ通し番号設定処理
	void SetTextureIndex(int index);
	void SetPosition(const D3DXVECTOR3& Pos);
	void SetRotation(const D3DXVECTOR3& Rot);
	//void SetFade(D3DXMATRIX& WorldMatrix);
};

#endif