//=====================================
//
// セレクトビュアー[SelectViewer.h]
// 機能：モードセレクト表示用
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _SELECTVIEWER_H_
#define _SELECTVIEWER_H_

#include "../../../main.h"
#include <vector>

class SubScreen;
class SelectCamera;
class SelectLogo;
//**************************************
// クラス定義
//**************************************
class SelectViewer
{
public:
	// 選択できるモードの数
	enum Mode {
		GameStart,
		TrophyCheck,
		Exit,
		Max
	};

	SelectViewer();
	~SelectViewer();
	void Update();
	void Draw();

	int CheckNextScene();
	// セレクトロゴの表示が"ゲーム開始"に設定する
	void InitSelectLogo(void);

private:
	SubScreen* subScreen;
	SelectCamera* camera;
	std::vector<SelectLogo*> logo;
	int nextMode;

	static const D3DXVECTOR2 SubScreenSize;
	static const D3DXVECTOR2 SubScreenPos;
};

#endif