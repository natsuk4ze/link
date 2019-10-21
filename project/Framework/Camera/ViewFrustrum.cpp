//=====================================
//
//ViewFrustrum.cpp
//機能:カメラの視錐台
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ViewFrustrum.h"

/**************************************
staticメンバ
***************************************/
const unsigned ViewFrustrum::VertexMax = 8;

/**************************************
コンストラクタ
***************************************/
ViewFrustrum::ViewFrustrum()
{
	vertexPos.resize(VertexMax, Vector3::Zero);
}

/**************************************
デストラクタ
***************************************/
ViewFrustrum::~ViewFrustrum()
{
	vertexPos.clear();
}

/**************************************
視錐台の面の法線取得処理
***************************************/
D3DXVECTOR3 ViewFrustrum::GetNormal(Surface surfaceID)
{
	D3DXVECTOR3 normal = Vector3::Up;
	switch (surfaceID)
	{
	case ViewFrustrum::Left:
		normal = _GetNormal(NearLeftTop, FarLeftTop, NearLeftBottom);
		break;

	case ViewFrustrum::Right:
		normal = _GetNormal(NearRightBottom, FarRightBottom, NearRightTop);
		break;

	case ViewFrustrum::Top:
		normal = _GetNormal(NearLeftTop, NearRightTop, FarLeftTop);
		break;

	case ViewFrustrum::Bottom:
		normal = _GetNormal(NearLeftBottom, FarLeftBottom, NearRightBottom);
		break;
	}

	return normal;
}

/**************************************
頂点設定処理
***************************************/
void ViewFrustrum::SetVertex(const D3DXVECTOR3 & NearLeftTop, const D3DXVECTOR3 & NearRightTop, const D3DXVECTOR3 & NearLeftBottom, const D3DXVECTOR3 & NearRightBottom, const D3DXVECTOR3 & FarLeftTop, const D3DXVECTOR3 & FarRightTop, const D3DXVECTOR3 & FarLeftBottom, const D3DXVECTOR3 & FarRightBottom)
{
	vertexPos[Vertex::NearLeftTop] = NearLeftTop;
	vertexPos[Vertex::NearRightTop] = NearRightTop;
	vertexPos[Vertex::NearLeftBottom] = NearLeftBottom;
	vertexPos[Vertex::NearRightBottom] = NearRightBottom;
	vertexPos[Vertex::FarLeftTop] = FarLeftTop;
	vertexPos[Vertex::FarRightTop] = FarRightTop;
	vertexPos[Vertex::FarLeftBottom] = FarLeftBottom;
	vertexPos[Vertex::FarRightBottom] = FarRightBottom;

}

/**************************************
法線取得処理（内部処理）
***************************************/
D3DXVECTOR3 ViewFrustrum::_GetNormal(int v1, int v2, int v3)
{
	return Vector3::Axis(vertexPos[v2] - vertexPos[v1], vertexPos[v3] - vertexPos[v1]);
}

/**************************************
面上のある一点を所得
***************************************/
D3DXVECTOR3 ViewFrustrum::GetSurfacePoint(Surface surfaceID)
{
	D3DXVECTOR3 ret = Vector3::Zero;
	switch (surfaceID)
	{
	case Left:
		ret = vertexPos[NearLeftTop];
		break;
	case Right:
		ret = vertexPos[NearRightTop];
		break;
	case Top:
		ret = vertexPos[NearLeftTop];
		break;
	case Bottom:
		ret = vertexPos[FarLeftBottom];
		break;
	default:
		break;
	}

	return ret;
}

/**************************************
視錐台カリング
***************************************/
bool ViewFrustrum::CheckOnCamera(const D3DXVECTOR3 pos)
{
	bool ret = false;

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 nor = GetNormal(Surface(i));
		D3DXVECTOR3 vec = pos - GetSurfacePoint(Surface(i));

		// 視錐台の法線と、視錐台からオブジェクトへのベクトルから内積計算
		float dot = D3DXVec3Dot(&nor, &vec);

		if (dot > 0)
		{
			ret = true;
		}
		else
		{
			ret = false;
			break;
		}
	}

	return ret;
}