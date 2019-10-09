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
#include "FieldConfig.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"

namespace Field
{
/**************************************
前方宣言
***************************************/
	class FieldCursorSquare;

	/**************************************
	FieldCursorクラス
	***************************************/
	class FieldCursor : public GameObject
	{
	public:
		//コンストラクタ、デストラクタ
		FieldCursor(float positionOffset);
		~FieldCursor();

		//更新処理、描画処理
		void Update();
		void Draw();

		//移動処理
		void Move(int x, int z);

		//移動範囲設定処理
		void SetBorder(int forward, int right, int back, int left);

		//座標取得
		FieldPosition GetModelPosition() const;

		//座標設定処理
		void SetModelPosition(int x, int z);

	private:
		const int SquareMax = 5;			//四角形最大数
		const int EmitInterval = 10;		//四角形生成インターバル
		const int MoveDuration = 4;			//移動時間
		const float PositionOffset;			//1マス毎の座標オフセット			

		int cntFrame;						//フレームカウント
		int cntMove;						//移動カウント

		FieldPosition position;				//座標
		FieldBorder fieldBorder;			//移動可能な範囲

		D3DXVECTOR3 moveTarget;				//移動の目標地点
		D3DXVECTOR3 startPos;				//移動のスタート地点

		std::vector<FieldCursorSquare*> squareContainer;	//四角形コンテナ

		//四角形セット処理
		void SetSquare();

		//移動内部処理
		void Move();

		//ワールド座標系酸処理
		D3DXVECTOR3 CalcWorldPosition() const;
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

		//比較関数
		static bool Compare(const FieldCursorSquare* lhs, const FieldCursorSquare* rhs);

	private:
		static const D3DXVECTOR2 Size;				//サイズ
		static const int FadeDuration;				//フェード時間
		static const float MoveSpeed;				//移動スピード

		int cntFrame;								//フレームカウント
		Transform *transform;						//SRT情報
	};
}

#endif