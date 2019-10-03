//=============================================================================
//
// カウントビュアー描画用処理 [CountViewerDrawer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "source/Viewer/Framework/ViewerDrawer/CountViewerDrawer.h"

//=============================================================================
// オブジェクトの頂点座標の設定　（カウンター専用）
//=============================================================================
void CountViewerDrawer::SetVertex(int placeCount, float placeInterval)
{
	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, -size.y, 0.0f);
	vertexWk[1].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, -size.y, 0.0f);
	vertexWk[2].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(-size.x, size.y, 0.0f);
	vertexWk[3].vtx = D3DXVECTOR3(position.x + placeCount * placeInterval, position.y, position.z)
		+ D3DXVECTOR3(size.x, size.y, 0.0f);
}

//=============================================================================
//オブジェクトのテクスチャ座標設定処理　（カウンター専用）
//=============================================================================
void CountViewerDrawer::SetTexture(int number, float placeInterval)
{
	// 頂点座標の設定
	vertexWk[0].tex = D3DXVECTOR2(number * placeInterval, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(number * placeInterval, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(number * placeInterval + placeInterval, 1.0f);
}

//=============================================================================
//カウンター描画処理
//=============================================================================
void CountViewerDrawer::DrawCounter(int baseNumber, int parameterBox, int placeMax, float intervalNumberScr, float intervalNumberTex)
{
	for (int nCntPlace = 0; nCntPlace < placeMax; nCntPlace++)
	{
		int num;

		num = parameterBox % (int)(pow(baseNumber, (placeMax - nCntPlace)))
			/ (int)(pow(baseNumber, (placeMax - nCntPlace - 1)));

		Draw();
		SetVertex(nCntPlace, intervalNumberScr);
		SetTexture(num, intervalNumberTex);
	}
}
