//=====================================
//
//MophingMeshContainer.h
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

/**************************************
クラス定義
***************************************/
class MophingMeshContainer : public MeshContainer
{
public:
	MophingMeshContainer();
	virtual ~MophingMeshContainer();

	void RegisterVertex(unsigned index);

private:
	std::vector<LPDIRECT3DVERTEXBUFFER9> vtxContainer;
};
#endif