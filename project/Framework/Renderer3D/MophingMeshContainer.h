//=====================================
//
//MorphingMeshContainer.h
//機能:モーフィングメッシュコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MOPHINGMESHCONTAINER_H_
#define _MOPHINGMESHCONTAINER_H_

#include "../../main.h"
#include "MeshContainer.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class MophingEffect;

/**************************************
クラス定義
***************************************/
class MorphingMeshContainer : public MeshContainer
{
public:
	//コンストラクタ、デストラクタ
	MorphingMeshContainer();
	virtual ~MorphingMeshContainer();

	//現在保持しているメッシュをモーフテーブルに登録する
	void RegisterVertex(unsigned index);

	//描画処理
	void Draw(const D3DXMATRIX& mtxWorld);

	//現在のメッシュを設定
	void SetCurrent(unsigned index);

	//モーフィング先を設定
	void SetNext(unsigned next);

	//変化量を設定
	void SetChange(float t);

	//登録したメッシュを解放
	void ReleaseRegistration();

private:
	//使用するメッシュ群
	std::vector<LPD3DXMESH> meshTable;

	//使用するテクスチャ群
	std::vector<std::vector<LPDIRECT3DTEXTURE9>> textureContainer;

	//使用するマテリアル群
	std::vector<std::vector<D3DMATERIAL9>> materialContainer;

	//インデックスバッファ
	LPDIRECT3DINDEXBUFFER9 indexBuff;

	//頂点情報
	DWORD fvf;
	LPDIRECT3DVERTEXDECLARATION9 declare;

	//頂点属性テーブル
	std::vector<D3DXATTRIBUTERANGE> attributeTable;

	//描画エフェクト
	MophingEffect *effect;

	//モーフィングインデックス
	int currentIndex, nextIndex;

	//変化量
	float t;

	//MeshContainerのDraw()を使わせたくないのでprivate化
	void Draw() override;
	void Draw(RendererEffect& effect) override;
};
#endif