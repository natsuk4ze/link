//=====================================
//
//FieldCursor.h
//機能:フィールドカーソル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCURSOR_H_
#define _FIELDCURSOR_H_

#include <vector>

#include "../../main.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"

/**************************************
前方宣言
***************************************/
class FieldCursorSquare;

/**************************************
FieldCursorクラス
***************************************/
class FieldCursor : GameObject
{
public:
	//コンストラクタ、デストラクタ
	FieldCursor();
	~FieldCursor();

	//更新処理、描画処理
	void Update();
	void Draw();

	//移動処理
	void Move(const D3DXVECTOR3& direction);

	//移動範囲設定処理
	void SetBorder(float borderX, float borderZ);

private:
	const int SquareMax = 5;			//四角形最大数
	const int EmitInterval = 30;		//四角形生成インターバル

	float borderX, borderZ;				//移動可能範囲
	int cntFrame;						//フレームカウント


	std::vector<FieldCursorSquare*> squareContainer;	//四角形コンテナ

	//四角形セット処理
	void SetSquare();
};

/**************************************
FieldCursorSquareクラス
***************************************/
class FieldCursorSquare : public BoardPolygon
{
public:
	//コンストラクタ、デストラクタ
	FieldCursorSquare();
	~FieldCursorSquare();

	//更新処理、描画処理
	void Update();
	void Draw(const D3DXMATRIX& parentMtx);

	//セット処理
	void Set();

	//アクティブ判定
	bool IsActive();

private:
	const D3DXVECTOR2 Size{ 10.0f, 10.0f };		//サイズ
	const int FadeDuration = 30;				//フェード時間
	const float MoveSpeed = 5.0f;				//移動スピード

	int cntFrame;					//フレームカウント
	Transform *transform;			//SRT情報
};

#endif