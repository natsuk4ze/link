//=====================================
//
//ViewFrustrum.h
//機能:カメラの視錐台
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _VIEWFRUSTRUM_H_
#define _VIEWFRUSTRUM_H_

#include "../../main.h"
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ViewFrustrum
{
public:
	//視錐台の面を表す列挙子
	enum Surface
	{
		Left,		//左面
		Right,		//右面
		Top,		//上面
		Bottom,		//下面
		Max,
	};

	//コンストラクタ、デストラクタ
	ViewFrustrum();
	~ViewFrustrum();

	//面の法線取得処理 ※正規化済み
	D3DXVECTOR3 GetNormal(Surface surfaceID);

	// 面上のある一点を取得
	D3DXVECTOR3 GetSurfacePoint(Surface surfaceID);

	//頂点設定処理
	void SetVertex(
		const D3DXVECTOR3& NearLeftTop, const D3DXVECTOR3& NearRightTop,
		const D3DXVECTOR3& NearLeftBottom, const D3DXVECTOR3& NearRightBottom,
		const D3DXVECTOR3& FarLeftTop, const D3DXVECTOR3& FarRightTop,
		const D3DXVECTOR3& FarLeftBottom, const D3DXVECTOR3& FarRightBottom);

private:
	//頂点最大数
	static const unsigned VertexMax;

	//頂点コンテナ
	std::vector<D3DXVECTOR3> vertexPos;

	//法線取得内部処理
	D3DXVECTOR3 _GetNormal(int v1, int v2, int v3);

	//頂点列挙子
	enum Vertex
	{
		NearLeftTop, 
		NearRightTop,
		NearLeftBottom,
		NearRightBottom,
		FarLeftTop,
		FarRightTop,
		FarLeftBottom,
		FarRightBottom
	};

};

#endif