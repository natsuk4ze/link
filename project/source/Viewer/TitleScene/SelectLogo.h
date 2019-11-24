//=====================================
//
// セレクトロゴ[SelectLogo.h]
// 機能：セレクトロゴ
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _SELECTLOGO_H_
#define _SELECTLOGO_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "SelectViewer.h"

//**************************************
// クラス定義
//**************************************
class SelectLogo :
	BillboardObject
{
private:
	BoardPolygon* polygon;

	// 移動判定
	bool moveRight;
	bool moveLeft;
	int counter;
	float angle;

	bool Moveable();	// 操作可能判定

	// スタティックメンバ
	static const float Distance;
	static const int MoveFrame;

public:
	SelectLogo();
	~SelectLogo();

	void Update();
	void Draw();

	void LoadResource(const char* tag);
	void SetPosition(const D3DXVECTOR3& pos);
	void SetTexDiv(const D3DXVECTOR2& div);
	void SetTextureIndex(const int& index);
	void TurnRight();	// 右に移動
	void TurnLeft();	// 左に移動
	void SetAngle(float angle);

	// 演算子のオーバーロード
	// 描画順ソートのため
	bool operator < (const SelectLogo& another)const
	{
		return transform->GetPosition().z < another.transform->GetPosition().z;
	}
	bool operator > (const SelectLogo& another)const
	{
		return transform->GetPosition().z > another.transform->GetPosition().z;
	}

	// スタティックメンバ
	static const D3DXVECTOR3 InitLogoPos[SelectViewer::Mode::Max];
};

#endif
