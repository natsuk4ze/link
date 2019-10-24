//=====================================
//
// ビューフラストラムボックス[ViewFrustrumBox.h]
// 機能：視錐台カリング用ボックス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "ViewFrustumBox.h"
#include <vector>
#include <algorithm>

//**************************************
// メンバ変数初期化
//**************************************
const float ViewFrustumBox::PlaceActorSize = 5.0f;
const float ViewFrustumBox::PassengerActorSize = 3.0f;

//=====================================
// コンストラクタ
//=====================================
ViewFrustumBox::ViewFrustumBox(const D3DXVECTOR3 pos, float size) :
	pos(pos)
{
	this->point[UpLeftFar] = this->pos + D3DXVECTOR3(-size, size, -size);
	this->point[UpRightFar] = this->pos + D3DXVECTOR3(size, size, -size);
	this->point[UpLeftNear] = this->pos + D3DXVECTOR3(-size, size, size);
	this->point[UpRightNear] = this->pos + D3DXVECTOR3(size, size, size);
	this->point[DownLeftFar] = this->pos + D3DXVECTOR3(-size, -size, -size);
	this->point[DownRightFar] = this->pos + D3DXVECTOR3(size, -size, -size);
	this->point[DownLeftNear] = this->pos + D3DXVECTOR3(-size, -size, size);
	this->point[DownRightNear] = this->pos + D3DXVECTOR3(size, -size, size);
}

//=====================================
// デストラクタ
//=====================================
ViewFrustumBox::~ViewFrustumBox()
{
}

//=====================================
// 対象から最短距離の座標を取得する
//=====================================
D3DXVECTOR3 ViewFrustumBox::SearchNearPoint(const D3DXVECTOR3 target)
{
	// 対象から座標への距離を計算
	std::vector<float> dist;
	dist.reserve(Point::Max);
	for (int i = 0; i < Point::Max; i++)
	{
		dist.push_back(D3DXVec3LengthSq(&(point[Point(i)] - target)));
	}

	// 最小値の添字を取得
	std::vector<float>::iterator minIt = std::min_element(dist.begin(), dist.end());
	size_t minIndex = std::distance(dist.begin(), minIt);

	return point[minIndex];
}

//=====================================
// 対象から最長距離の座標を取得する
//=====================================
D3DXVECTOR3 ViewFrustumBox::SearchFarPoint(const D3DXVECTOR3 target)
{
	// 対象から座標への距離を計算
	std::vector<float> dist;
	dist.reserve(Point::Max);
	for (int i = 0; i < Point::Max; i++)
	{
		dist.push_back(D3DXVec3LengthSq(&(point[Point(i)] - target)));
	}

	// 最大値の添字を取得
	std::vector<float>::iterator maxIt = std::max_element(dist.begin(), dist.end());
	size_t maxIndex = std::distance(dist.begin(), maxIt);

	return point[maxIndex];
}
