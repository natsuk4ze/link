//=====================================
//
//CircleGauge.h
//機能:円形ゲージ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CIRCLEGAUGE_H_
#define _CIRCLEGAUGE_H_

#include "../../main.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class CircleGauge
{
public:
	//どこをゲージの始点にするか
	enum FillStart
	{
		Right,		//右端
		Top,		//上端
		Left,		//左端
		Bottom		//下端
	};

	//コンストラクタ、デストラクタ
	CircleGauge(const D3DXVECTOR2& Size);
	~CircleGauge();

	//描画処理
	void Draw();

	//テクスチャ読み込み処理
	void LoadTexture(const char* path);

	//SRT情報設定処理
	void SetPosition(const D3DXVECTOR3& pos);
	void SetRotation(const D3DXVECTOR3& rot);	//ラジアンではなく角度をそのまま渡す
	void SetScale(const D3DXVECTOR3& scale);

	//パーセント設定処理(0.0 ~ 1.0)
	void SetPercent(float per);

	//始点設定処理
	void SetFillStart(FillStart start);

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;		//頂点バッファ
	LPDIRECT3DTEXTURE9 texture;				//テクスチャ

	Transform* transform;					//SRT情報

	LPD3DXEFFECT effect;					//エフェクト

	float percent;							//ゲージの表示%
	FillStart start;						//ゲージの始点

	//シェーダのグローバル変数へのハンドル
	D3DXHANDLE hPercent;
	D3DXHANDLE hMatrix;
	D3DXHANDLE hProj;
};

#endif